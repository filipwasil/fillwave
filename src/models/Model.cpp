/*
 * Model.cpp
 *
 *  Created on: Jun 12, 2014
 *
 */

#include <fillwave/Fillwave.h>
#include <fillwave/actions/callbacks/TimedBoneUpdateCallback.h>

#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/models/Model.h>
#include <fillwave/models/animations/Animator.h>
#include <fillwave/models/animations/Conversion.h>
#include <fillwave/models/animations/Animation.h>

#include <fillwave/Log.h>
#include <fillwave/management/LightSystem.h>
#include <fillwave/management/TextureSystem.h>

FLOGINIT("Model", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Model::Model(
   Engine* engine,
   core::Program* program,
   Shape<core::VertexBasic>& shape,
   core::Texture2D* diffuseMap,
   core::Texture2D* normalMap,
   core::Texture2D* specularMap,
   const Material& material) :
	Programmable(program),
	mAnimator(nullptr),
	mLights(engine->getLightSystem()),
	mAnimationCallback(nullptr),
	mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE) {

	initShadowing(engine);

	ProgramLoader loader(engine);

	std::vector<core::VertexBasic> vertices = shape.getVertices();
	std::vector<GLuint> indices = shape.getIndices();

	attach(std::make_shared<Mesh>(engine, material, diffuseMap,
	                              normalMap, specularMap,
	                              program, mProgramShadow, mProgramShadowColor,
	                              loader.getOcclusionOptimizedQuery(),
	                              loader.getAmbientOcclusionGeometry(),
	                              loader.getAmbientOcclusionColor(), engine->getLightSystem(),
	                              new core::VertexBufferBasic (vertices),
	                              new core::IndexBufferBasic (indices), mAnimator));
}

Model::Model(Engine* engine, core::Program* program,
             const std::string& shapePath) :
	Programmable(program),
	mAnimator(nullptr),
	mLights(engine->getLightSystem()),
	mAnimationCallback(nullptr),
	mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE) {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	const aiScene* scene = engine->getModelFromFile(shapePath);

	if (scene) {
		initAnimations(scene);
		initShadowing(engine);
		initUniformsCache();
		loadNodes(scene->mRootNode, scene, engine, this);
	} else {
		FLOG_FATAL("Model: %s could not be read", shapePath.c_str());
	}
#else
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	if (!tinyobj::LoadObj(shapes, materials, err, shapePath.c_str())) {
		FLOG_FATAL("Model: %s could not be read", shapePath.c_str());
	}
	if (!err.empty()) { // `err` may contain warning message.
	  FLOG_WARNING("%s", err.c_str());
	}

	FLOG_DEBUG("Shapes    : %d", shapes.size());
	FLOG_DEBUG("Materials : %d", materials.size());

	for (size_t i = 0; i < shapes.size(); i++) {
	  printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
	  printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
	  printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
//	  assert((shapes[i].mesh.indices.size() % 3) == 0);
	  for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
	    printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3*f+0], shapes[i].mesh.indices[3*f+1], shapes[i].mesh.indices[3*f+2], shapes[i].mesh.material_ids[f]);
	  }

	  printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
	  assert((shapes[i].mesh.positions.size() % 3) == 0);
	  for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
	    printf("  v[%ld] = (%f, %f, %f)\n", v,
	      shapes[i].mesh.positions[3*v+0],
	      shapes[i].mesh.positions[3*v+1],
	      shapes[i].mesh.positions[3*v+2]);
	  }
	}

	for (size_t i = 0; i < materials.size(); i++) {
	  printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
	  printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
	  printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
	  printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
	  printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
	  printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
	  printf("  material.Ns = %f\n", materials[i].shininess);
	  printf("  material.Ni = %f\n", materials[i].ior);
	  printf("  material.dissolve = %f\n", materials[i].dissolve);
	  printf("  material.illum = %d\n", materials[i].illum);
	  printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
	  printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
	  printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
	  printf("  material.map_Ns = %s\n", materials[i].specular_highlight_texname.c_str());
	  std::map<std::string, std::string>::const_iterator it(materials[i].unknown_parameter.begin());
	  std::map<std::string, std::string>::const_iterator itEnd(materials[i].unknown_parameter.end());
	  for (; it != itEnd; it++) {
	    printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
	  }
	  printf("\n");
	}

	for (GLuint i = 0; i < shapes.size(); i++) {

		std::string diffuseMapPath, normalMapPath, specularMapPath;

		entity->attach(
		   loadMesh(shapes[i], Material(aMaterial),
		            engine->storeTexture(diffuseMapPath.c_str()),
		            engine->storeTexture(normalMapPath.c_str()),
		            engine->storeTexture(specularMapPath.c_str()),
		            engine));
	}
	#error "Not ready"
#endif
}

Model::Model(
   Engine* engine,
   core::Program* program,
   const std::string& shapePath,
   const std::string& diffuseMapPath,
   const std::string& normalMapPath,
   const std::string& specularMapPath) :
	Programmable(program),
	mAnimator(nullptr),
	mLights(engine->getLightSystem()),
	mAnimationCallback(nullptr),
	mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE) {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
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
#else
	#error "Not ready"
#endif
}

Model::Model(
   Engine* engine,
   core::Program* program,
   const std::string& shapePath,
   core::Texture2D* diffuseMap,
   core::Texture2D* normalMap,
   core::Texture2D* specularMap,
   const Material& material) :
	Programmable(program),
	mAnimator(nullptr),
	mLights(engine->getLightSystem()),
	mAnimationCallback(nullptr),
	mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE) {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
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
#else
	#error "Not ready"
#endif
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

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
inline void Model::initAnimations(const aiScene* scene) {
	if (scene->HasAnimations()) {
		mAnimator = new Animator(scene);
		FLOG_DEBUG("attached TimedBoneUpdateCallback to model");
		mAnimationCallback = new TimedBoneUpdateCallback(this);
		this->attachHierarchyCallback(mAnimationCallback);
	}
}

inline void Model::loadNodes(
   aiNode* node,
   const aiScene* scene,
   Engine* engine,
   Entity* entity,
   const std::string& diffuseMapPath,
   const std::string& normalMapPath,
   const std::string& specularMapPath) {

	/* Set this node transformations */

	loadNodeTransformations(node, entity);

	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		const aiMesh* aMesh = scene->mMeshes[node->mMeshes[i]];
		const aiMaterial* aMaterial = scene->mMaterials[aMesh->mMaterialIndex];

		entity->attach(
		   loadMesh(aMesh, Material(aMaterial),
		            engine->storeTexture(diffuseMapPath.c_str()),
		            engine->storeTexture(normalMapPath.c_str()),
		            engine->storeTexture(specularMapPath.c_str()),
		            engine));
	}

	/* Evaluate children */
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		pEntity newEntity = buildHinge();
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
		const aiMesh* aMesh = scene->mMeshes[node->mMeshes[i]];
		const aiMaterial* aMaterial = scene->mMaterials[aMesh->mMaterialIndex];

		aiString diffuseMapPathAssimp, normalMapPathAssimp, specularMapPathAssimp;
		std::string diffuseMapPath, normalMapPath, specularMapPath;

		diffuseMapPath =
		   (aMaterial->GetTexture(
		       aiTextureType_DIFFUSE, 0, &diffuseMapPathAssimp, nullptr,
		       nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) ?
		   diffuseMapPathAssimp.data : "255_255_255.color";

		normalMapPath =
		   (aMaterial->GetTexture(
		       aiTextureType_NORMALS, 0, &normalMapPathAssimp, nullptr,
		       nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) ?
		   normalMapPathAssimp.data : "128_128_255.color";

		specularMapPath =
		   (aMaterial->GetTexture(
		       aiTextureType_SPECULAR, 0, &specularMapPathAssimp, nullptr,
		       nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) ?
		   specularMapPathAssimp.data : "";

		entity->attach(
		   loadMesh(aMesh, Material(aMaterial),
		            engine->storeTexture(diffuseMapPath.c_str()),
		            engine->storeTexture(normalMapPath.c_str()),
		            engine->storeTexture(specularMapPath.c_str()),
		            engine));
	}

	/* Evaluate children */
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		pEntity newEntity = buildHinge();
		entity->attach(newEntity);
		loadNodes(node->mChildren[i], scene, engine, newEntity.get());
	}
}

inline void Model::loadNodes(
   aiNode* node,
   const aiScene* scene,
   Engine* engine,
   Entity* entity,
   core::Texture2D* diffuseMap,
   core::Texture2D* normalMap,
   core::Texture2D* specularMap,
   const Material& material) {

	/* Set this node transformations */

	loadNodeTransformations(node, entity);

	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		const aiMesh* aMesh = scene->mMeshes[i];
		pMesh mesh = loadMesh(aMesh, material, diffuseMap,
		                      normalMap, specularMap,
		                      engine);
		entity->attach(mesh);
	}

	/* Evaluate children */
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		pEntity newEntity = buildHinge();
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
   const aiMesh* shape,
   const Material& material,
   core::Texture2D* diffuseMap,
   core::Texture2D* normalMap,
   core::Texture2D* specularMap,
   Engine* engine) {

	if (!shape) {
		return nullptr;
	}

	ProgramLoader loader(engine);
	core::VertexArray* vao = new core::VertexArray();
	return std::make_shared < Mesh
	       > (engine, material, diffuseMap, normalMap, specularMap, mProgram,
	          mProgramShadow, mProgramShadowColor, loader.getOcclusionOptimizedQuery(),
	          loader.getAmbientOcclusionGeometry(), loader.getAmbientOcclusionColor(),
	          engine->getLightSystem(), engine->storeBuffer<core::VertexBufferBasic> (vao, shape, mAnimator),
				 engine->storeBuffer<core::IndexBufferBasic>(vao, shape), mAnimator, GL_TRIANGLES, vao);
}
#else /* FILLWAVE_MODEL_LOADER_ASSIMP */

pMesh loadMesh(tinyobj::shape_t& shape,
	   const Material& material,
	   core::Texture2D* diffuseMap,
	   core::Texture2D* normalMap,
	   core::Texture2D* specularMap,
	   Engine* engine) {
#error "Not ready"
	return pMesh();
}
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

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
	if (mAnimator) {
		/* xxx for PBRP shadows must be updated elsewhere */
		mAnimator->updateBonesBuffer();
		mAnimator->updateBonesUniform(mUniformLocationCacheBones);
	}

	mLights->pushLightUniforms(mProgram);
	mLights->bindShadowmaps();

	drawWithEffectsPBRP(camera);
}

void Model::drawDR(ICamera& camera) {
	evaluateAnimations();
	drawWithEffectsDR(camera);
}

void Model::log() const {

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
	ProgramLoader loader(engine);
	if (mAnimator) {
		mProgramShadow = loader.getShadowWithAnimation();
		mProgramShadowColor = loader.getShadowColorCodedWithAnimation();
	} else {
		mProgramShadow = loader.getShadow();
		mProgramShadowColor = loader.getShadowColorCoded();
	}
}

bool Model::isAnimated() const {
	return mAnimator ? GL_TRUE : GL_FALSE;
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

void Model::updateRenderer(IRenderer& renderer) {
	renderer.update(this);
}

pModel buildModel(
   Engine* engine,
   core::Program* program,
   framework::Shape<core::VertexBasic>& shape,
   core::Texture2D* diffuseMap,
   core::Texture2D* normalMap,
   core::Texture2D* specularMap,
   framework::Material material) {
	return std::make_shared < framework::Model
	       > (engine, program, shape, diffuseMap, normalMap, specularMap, material);
}

} /* framework */
pModel buildModel(
   Engine* engine,
   core::Program* program,
   const std::string& shapePath,
   const std::string& diffuseMapPath,
   const std::string& normalMapPath,
   const std::string& specularMapPath) {
	return std::make_shared < framework::Model
	       > (engine, program, shapePath, diffuseMapPath, normalMapPath, specularMapPath);
}

pModel buildModel(
   Engine* engine,
   core::Program* program,
   const std::string& shapePath,
   core::Texture2D* diffuseMap,
   core::Texture2D* normalMap,
   core::Texture2D* specularMap,
   framework::Material material) {
	return std::make_shared < framework::Model
	       > (engine, program, shapePath, diffuseMap, normalMap, specularMap, material);
}

pModel buildModel(
   Engine* engine,
   core::Program* program,
   const std::string& shapePath) {
	return std::make_shared < framework::Model > (engine, program, shapePath);
}

} /* fillwave */
