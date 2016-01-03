/*
 * Model.cpp
 *
 *  Created on: Jun 12, 2014
 *
 */

#include <fillwave/Fillwave.h>
#include <fillwave/actions/callbacks/TimedBoneUpdateCallback.h>

#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/management/TextureManager.h>

#include <fillwave/models/Model.h>
#include <fillwave/models/animations/Animator.h>
#include <fillwave/models/animations/Conversion.h>
#include <fillwave/models/animations/Animation.h>

#include <fillwave/Log.h>

FLOGINIT("Model", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Model::Model(
		Engine* engine,
		pProgram program,
		Shape<core::VertexBasic>& shape,
		pTexture diffuseMap,
		pTexture normalMap,
		pTexture specularMap,
		const Material& material)
		:
				Programmable(program),
				mAnimator(nullptr),
				mAnimationCallback(nullptr),
				mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE) {

	initShadowing(engine);

	ProgramLoader loader;

	std::vector<core::VertexBasic> vertices = shape.getVertices();
	std::vector<GLuint> indices = shape.getIndices();

	pMesh ptr = pMesh(
			new Mesh(engine, material, buildTextureRegion(diffuseMap),
					buildTextureRegion(normalMap), buildTextureRegion(specularMap),
					program, mProgramShadow, mProgramShadowColor,
					loader.getOcclusionOptimizedQuery(engine),
					loader.getAmbientOcclusionGeometry(engine),
					loader.getAmbientOcclusionColor(engine),
					engine->getLightManager(),
					pVertexBufferBasic(new core::VertexBufferBasic(vertices)),
					pIndexBufferBasic(new core::IndexBufferBasic(indices)),
					mAnimator));
	attach(ptr);
}

Model::Model(Engine* engine, pProgram program, const std::string& shapePath)
		:
				Programmable(program),
				mAnimator(nullptr),
				mAnimationCallback(nullptr),
				mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE) {

	const aiScene* scene = engine->getModelFromFile(shapePath);

	if (scene) {
		initAnimations(scene);
		initShadowing(engine);
		initUniformsCache();
		loadNodes(scene->mRootNode, scene, engine, this);
	} else {
		FLOG_FATAL("Model: %s could not be read", shapePath.c_str());
	}
}

Model::Model(
		Engine* engine,
		pProgram program,
		const std::string& shapePath,
		const std::string& diffuseMapPath,
		const std::string& normalMapPath,
		const std::string& specularMapPath)
		:
				Programmable(program),
				mAnimator(nullptr),
				mAnimationCallback(nullptr),
				mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE) {

	const aiScene* scene = engine->getModelFromFile(shapePath);
	if (scene) {
		initAnimations(scene);
		initShadowing(engine); //xxx must be after initAnimations
		initUniformsCache();
		loadNodes(scene->mRootNode, scene, engine, this, diffuseMapPath,
				normalMapPath, specularMapPath);
	} else {
		FLOG_FATAL("Model: %s could not be read", shapePath.c_str());
	}
}

Model::Model(
		Engine* engine,
		pProgram program,
		const std::string& shapePath,
		pTexture diffuseMap,
		pTexture normalMap,
		pTexture specularMap,
		const Material& material)
		:
				Programmable(program),
				mAnimator(nullptr),
				mAnimationCallback(nullptr),
				mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE) {

	const aiScene* scene = engine->getModelFromFile(shapePath);
	if (scene) {
		initAnimations(scene);
		initShadowing(engine);
		initUniformsCache();
		loadNodes(scene->mRootNode, scene, engine, this, diffuseMap, normalMap,
				specularMap, material);
	} else {
		FLOG_FATAL("Model: %s could not be read", shapePath.c_str());
	}
}

Model::~Model() {
	if (mAnimationCallback) {
		delete mAnimationCallback; //xxx this the source of all problems in double free
	}
	if (mAnimator) {
		delete mAnimator;
	}
}

void Model::reload() {

}

inline void Model::loadNodes(
		fNode* node,
		const fScene* scene,
		Engine* engine,
		Entity* entity,
		const std::string& diffuseMapPath,
		const std::string& normalMapPath,
		const std::string& specularMapPath) {

	/* Set this node transformations */

	loadNodeTransformations(node, entity);

	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		const fMesh* aMesh = scene->mMeshes[node->mMeshes[i]];
		const fMaterial* aMaterial = scene->mMaterials[aMesh->mMaterialIndex];

		pMesh mesh = loadMesh(aMesh, Material(aMaterial),
				buildTextureRegion(
						engine->storeTexture(diffuseMapPath.c_str(),
								aiTextureType_DIFFUSE)),
				buildTextureRegion(
						engine->storeTexture(normalMapPath.c_str(),
								aiTextureType_NORMALS)),
				buildTextureRegion(
						engine->storeTexture(specularMapPath.c_str(),
								aiTextureType_SPECULAR)), engine);
		entity->attach(mesh);
	}

	/* Evaluate children */
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		pEntity newEntity = buildEntity();
		entity->attach(newEntity);
		loadNodes(node->mChildren[i], scene, engine, newEntity.get(),
				diffuseMapPath, normalMapPath, specularMapPath);
	}
}

inline void Model::loadNodes(
		aiNode* node,
		const aiScene* scene,
		Engine* engine,
		Entity* entity) {

	/* Set this node transformations */

	loadNodeTransformations(node, entity);

	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		const fMesh* aMesh = scene->mMeshes[node->mMeshes[i]];
		const fMaterial* aMaterial = scene->mMaterials[aMesh->mMaterialIndex];

		fString diffuseMapPathAssimp, normalMapPathAssimp, specularMapPathAssimp;
		std::string diffuseMapPath, normalMapPath, specularMapPath;

		diffuseMapPath =
				(aMaterial->GetTexture(
				FILLWAVE_TEXTURE_TYPE_DIFFUSE, 0, &diffuseMapPathAssimp, nullptr,
						nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) ?
						diffuseMapPathAssimp.data : "255_255_255.color";

		normalMapPath =
				(aMaterial->GetTexture(
				FILLWAVE_TEXTURE_TYPE_NORMALS, 0, &normalMapPathAssimp, nullptr,
						nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) ?
						normalMapPathAssimp.data : "128_128_255.color";

		specularMapPath =
				(aMaterial->GetTexture(
				FILLWAVE_TEXTURE_TYPE_SPECULAR, 0, &specularMapPathAssimp, nullptr,
						nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) ?
						specularMapPathAssimp.data : "";

		pMesh mesh = loadMesh(aMesh, Material(aMaterial),
				buildTextureRegion(engine->storeTexture(diffuseMapPath.c_str(),
				FILLWAVE_TEXTURE_TYPE_DIFFUSE)),
				buildTextureRegion(engine->storeTexture(normalMapPath.c_str(),
				FILLWAVE_TEXTURE_TYPE_NORMALS)),
				buildTextureRegion(engine->storeTexture(specularMapPath.c_str(),
				FILLWAVE_TEXTURE_TYPE_SPECULAR)), engine);
		entity->attach(mesh);
	}

	/* Evaluate children */
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		pEntity newEntity = buildEntity();
		entity->attach(newEntity);
		loadNodes(node->mChildren[i], scene, engine, newEntity.get());
	}
}

inline void Model::loadNodes(
		aiNode* node,
		const aiScene* scene,
		Engine* engine,
		Entity* entity,
		pTexture diffuseMap,
		pTexture normalMap,
		pTexture specularMap,
		const Material& material) {

	/* Set this node transformations */

	loadNodeTransformations(node, entity);

	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		const fMesh* aMesh = scene->mMeshes[i];
		pMesh mesh = loadMesh(aMesh, material, buildTextureRegion(diffuseMap),
				buildTextureRegion(normalMap), buildTextureRegion(specularMap),
				engine);
		entity->attach(mesh);
	}

	/* Evaluate children */
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		pEntity newEntity = buildEntity();
		entity->attach(newEntity);
		loadNodes(node->mChildren[i], scene, engine, newEntity.get(), diffuseMap,
				normalMap, specularMap, material);
	}
}

inline void Model::loadNodeTransformations(aiNode* node, Entity* entity) {
	aiVector3t<float> scale;
	aiQuaterniont<float> rotation;
	aiVector3t<float> position;
	node->mTransformation.Decompose(scale, rotation, position);
	entity->scaleTo(assimpToGlmVec3(scale));
	entity->rotateTo(assimpToGlmQuat(rotation));
	entity->moveTo(assimpToGlmVec3(position));
}

pMesh Model::loadMesh(
		const fMesh* shape,
		const Material& material,
		pTextureRegion diffuseMap,
		pTextureRegion normalMap,
		pTextureRegion specularMap,
		Engine* engine) {

	ProgramLoader loader;

	if (shape) {
		pMesh ptr = pMesh(
				new Mesh(engine, material, diffuseMap, normalMap, specularMap,
						mProgram, mProgramShadow, mProgramShadowColor,
						loader.getOcclusionOptimizedQuery(engine),
						loader.getAmbientOcclusionGeometry(engine),
						loader.getAmbientOcclusionColor(engine),
						engine->getLightManager(),
						pVertexBufferBasic(
								new core::VertexBufferBasic(shape, mAnimator)),
						pIndexBufferBasic(new core::IndexBufferBasic(shape)),
						mAnimator));
		return ptr;
	} else {
		return pMesh();
	}
}

void Model::performAnimation(GLfloat timeElapsed_s) {
	mAnimator->updateTransformations(mActiveAnimation, timeElapsed_s);
}

void Model::setActiveAnimation(GLint animationID) {
	if (mAnimator->getAnimations() > animationID) {
		mActiveAnimation = animationID;
	} else {
		FLOG_ERROR("There is no animation for slot: %d", animationID);
		FLOG_DEBUG("Maximum number of animations: %d",
				mAnimator->getAnimations());
	}
}

GLint Model::getActiveAnimations() {
	return mAnimator->getAnimations();
}

void Model::draw(ICamera& camera) {
	evaluateAnimations();
	drawWithEffects(camera);
}

void Model::drawPBRP(ICamera& camera) {
	FLOG_ERROR("DEBUG1");
	if (mAnimator) {
		/* xxx for PBRP shadows must be updated elsewhere */
		mAnimator->updateBonesBuffer();
		mAnimator->updateBonesUniform(mUniformLocationCacheBones);
	}
	for (auto& it : mChildren) {
		it->drawPBRP(camera);
	}
}

void Model::drawDR(ICamera& camera) {
	evaluateAnimations();
	drawWithEffectsDR(camera);
}

void Model::log() const {

}

void Model::updateRenderpass(std::unordered_map<GLuint, std::vector<Entity*> >& renderpasses) {
	GLuint handle = mProgram.get()->getHandle();
	if (renderpasses.find(handle) != renderpasses.end()) {
		renderpasses[handle].push_back(this);
	} else {
		std::vector<Entity*> vector; /* xxx some base size maybe ? */
		vector.push_back(this);
		renderpasses[handle] = vector;
	}
}

inline void Model::initUniformsCache() {
	if (mAnimator) {
		mUniformLocationCacheBones = mProgram->getUniformLocation("uBones[0]");
		mUniformLocationCacheBonesShadow = mProgramShadow->getUniformLocation(
				"uBones[0]");
		mUniformLocationCacheBonesShadowColor =
				mProgramShadowColor->getUniformLocation("uBones[0]");
	}
}

inline void Model::initShadowing(Engine* engine) {
	ProgramLoader loader;
	if (mAnimator) {
		mProgramShadow = loader.getShadowWithAnimation(engine);
		mProgramShadowColor = loader.getShadowColorCodedWithAnimation(engine);
	} else {
		mProgramShadow = loader.getShadow(engine);
		mProgramShadowColor = loader.getShadowColorCoded(engine);
	}
}

inline void Model::initAnimations(const fScene* scene) {
	if (scene->HasAnimations()) {
		mAnimator = new Animator(scene);
		FLOG_DEBUG("attached TimedBoneUpdateCallback to model");
		mAnimationCallback = new TimedBoneUpdateCallback(this);
		this->attachHierarchyCallback(mAnimationCallback);
	}
}

inline void Model::evaluateAnimations() {
	if (mAnimator) {
		mAnimator->updateBonesBuffer();
		mProgram->use();
		mAnimator->updateBonesUniform(mUniformLocationCacheBones);
		mProgramShadow->use();
		mAnimator->updateBonesUniform(mUniformLocationCacheBonesShadow);
		mProgramShadowColor->use();
		mAnimator->updateBonesUniform(mUniformLocationCacheBonesShadowColor);
	}
}
} /* framework */
} /* fillwave */
