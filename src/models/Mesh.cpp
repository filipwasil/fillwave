/*
 * Fillwave
 *
 */

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2015] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/models/Mesh.h>

#include <fillwave/management/LightManager.h>
#include <fillwave/management/BoneManager.h>

#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/extras/string.h>

#include <fillwave/Profiler.h>

FLOGINIT("Mesh", FERROR | FFATAL | FINFO)

using namespace std;

namespace fillwave {
namespace models {

const GLint gOQVertices = 36;

Mesh::Mesh(
		Engine* engine,
		const Material& material,
		pTextureRegion diffuseMap,
		pTextureRegion normalMap,
		pTextureRegion specularMap,
		pProgram program,
		pProgram programShadow,
		pProgram programShadowColor,
		pProgram programOcclusion,
		pProgram programAmbientOcclusionGeometry,
		pProgram programAmbientOcclusionColor,
		manager::LightManager* lightManager,
		pVertexBufferBasic vbo,
		pIndexBufferBasic ibo,
		manager::BoneManager* boneManager,
		GLenum drawType)
		:
				Entity(),
				Reloadable(engine),
				mMaterial(material),
				mDiffuseMap(diffuseMap),
				mNormalMap(normalMap),
				mSpecularMap(specularMap),
				mProgram(program),
				mProgramShadow(programShadow),
				mProgramShadowColor(programShadowColor),
				mProgramOQ(programOcclusion),
				mProgramAOGeometry(programAmbientOcclusionGeometry),
				mProgramAOColor(programAmbientOcclusionColor),
				mIBO(ibo),
				mVBO(vbo),
				mLightManager(lightManager),
				mBoneManager(boneManager),
				mDrawType(drawType)
#ifdef __ANDROID__

#else
						,
				mConditionalRendering(GL_QUERY_WAIT)
#endif
{
	initPipeline();
	initVBO();
	initVAO();
	initUniformsCache();
}

Mesh::~Mesh() {

}

void Mesh::draw(space::Camera& camera) {
	/* Parent-children transformations */
	updateMatrixTree();

	if (mBoneManager || mOcclusionQuery.getResultAsync(1)) {

		mProgram->use();

		core::Uniform::push(mULCModelMatrix, mTransformation);
		core::Uniform::push(mULCLightAmbientIntensity, mMaterial.getAmbient());
		core::Uniform::push(mULCLightDiffuseIntensity, mMaterial.getDiffuse());
		core::Uniform::push(mULCLightSpecularIntensity, mMaterial.getSpecular());
		core::Uniform::push(mULCCameraPosition, camera.getTranslation());
		core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());

		mLightManager->pushLightUniforms(camera, mProgram.get());

		coreDraw();
	}
}

void Mesh::drawDR(space::Camera& camera) {
	/* Parent-children transformations */
	updateMatrixTree();
	if (mBoneManager || mOcclusionQuery.getResultAsync(1)) {

		mProgram->use();

		core::Uniform::push(mULCModelMatrix, mTransformation);
		core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());

		//   core::Uniform::push(mULCLightAmbientIntensity, mMaterial.getAmbient());
		//   core::Uniform::push(mULCLightDiffuseIntensity, mMaterial.getDiffuse());
		//   core::Uniform::push(mULCLightSpecularIntensity, mMaterial.getSpecular());
		//   core::Uniform::push(mULCCameraPosition, camera.getTranslation());

//      mLightManager->pushLightUniformsShadowMaps(mProgram.get());

		mLightManager->pushLightUniformsDR(camera, mProgram.get());

		coreDraw();
	}
}

void Mesh::drawFast(space::Camera& camera) {
	updateMatrixTree();
	mProgram->use();
	coreDraw();
}

inline void Mesh::coreDraw() {
	mVAO->bind();

	mLightManager->bindShadowmaps();

	bindTextures();

	//xxx blinking scene
	//xxx (OpenGL 3.3+)consider using conditional rendering this way:
	//#ifdef __ANDROID__
	//#else
	//   mConditionalRendering.begin(mOcclusionQuery.getID());
	onDraw();
	//   mConditionalRendering.end();
	//
	//#endif

	mVAO->unbind();

	core::Texture2D::unbind2DTextures();

	core::Program::disusePrograms();
}

inline void Mesh::bindTextures() {
	if (mDiffuseMap->getTexture()) {
		mDiffuseMap->getTexture()->bind(FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used
	}

	if (mNormalMap->getTexture()) {
		mNormalMap->getTexture()->bind(FILLWAVE_NORMAL_UNIT); //xxx texture region coordinates are not used
	}

	if (mSpecularMap->getTexture()) {
		mSpecularMap->getTexture()->bind(FILLWAVE_SPECULAR_UNIT); //xxx texture region coordinates are not used
	}
}

void Mesh::drawPicking(space::Camera& camera) {
	if (isPickable()) {
		mProgram->use();

		core::Uniform::push(mULCModelMatrix, mTransformation);

		core::Uniform::push(mULCCameraPosition, camera.getTranslation());
		core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());

		core::Uniform::push(mULCColorPicking, true);
		core::Uniform::push(mULCPainterColor, glm::vec4(getPickableColor(), 1.0));

		mVAO->bind();

		onDraw();

		mVAO->unbind();

		core::Uniform::push(mULCColorPicking, false);

		core::Program::disusePrograms();
	}
}

void Mesh::drawOcclusionBox(space::Camera& camera) {

	mProgramOQ->use();

	core::Uniform::push(mULCMVPOcclusion,
			camera.getViewProjection() * mTransformation * mOcclusionMatrix);

	mOcclusionQuery.begin();

	glDrawArrays(GL_TRIANGLES, 0, gOQVertices);

	FLOG_CHECK("drawOcclusionBox failed");

	mOcclusionQuery.end();

	core::Program::disusePrograms();
}

void Mesh::drawDepth(space::Camera& camera) {
	if (isPSC()) {
		mProgramShadow->use();

		core::Uniform::push(mULCMVPShadow,
				camera.getViewProjection() * mTransformation);

		mVAO->bind();

		onDraw();

		mVAO->unbind();

		core::Program::disusePrograms();
	}
}

void Mesh::drawDepthColor(space::Camera& camera, glm::vec3& position) {
	if (isPSC()) {
		mProgramShadowColor->use();

		core::Uniform::push(mULCMVPShadowColor,
				camera.getViewProjection() * mTransformation);
		core::Uniform::push(mULCModelMatrixShadowColor, mTransformation);

		mVAO->bind();

		onDraw();

		mVAO->unbind();

		core::Program::disusePrograms();
	}
}

void Mesh::drawAOG(space::Camera& camera) {
	/* Parent-children transformations */
//      updateMatrixTree();
	mProgramAOGeometry->use();

	core::Uniform::push(mULCMVPAmbientOcclusion,
			camera.getViewProjection() * mTransformation);
	core::Uniform::push(mULCPositionAmbientOcclusion,
			camera.getEye() * mTransformation);

	mVAO->bind();

	onDraw();

	mVAO->unbind();
}

void Mesh::drawAOC(space::Camera& camera) {
	mProgramAOColor->use();

//      core::Uniform::push(mULCTextureMap, FILLWAVE_DIFFUSE_ATTACHMENT);
	core::Uniform::push(mULCSampleRadius, FILLWAVE_AO_SAMPLE_RADIUS);
	core::Uniform::push(mULCProjectionMatrix, camera.getProjection());
//      core::Uniform::push(mULCRandomVectors, camera.getEye() * mTransformation);

	mVAO->bind();

	onDraw();

	mVAO->unbind();
}

void Mesh::onDraw() {
	if (mIBO) {
		/* Perform index drawing */
		glDrawElements(mDrawType, mIBO->getElements(), GL_UNSIGNED_INT,
				(GLvoid*) 0);
		FLOG_CHECK("glDrawElements failed");
	} else {
		/* Perform array drawing */
		glDrawArrays(mDrawType, 0, mVBO->getElements());
		FLOG_CHECK("glDrawArrays failed");
	}
}

inline void Mesh::initPipeline() {
	if (mProgram) {
		loader::ProgramLoader::initDefaultUniforms(mProgram.get());
	}
}

inline void Mesh::initUniformsCache() {
	/* Regular program */
	if (mProgram) {
		mULCModelMatrix = mProgram->getUniformLocation("uModelMatrix");
		mULCLightAmbientIntensity = mProgram->getUniformLocation(
				"uLightAmbientIntensity");
		mULCLightDiffuseIntensity = mProgram->getUniformLocation(
				"uLightDiffuseIntensity");
		mULCLightSpecularIntensity = mProgram->getUniformLocation(
				"uLightSpecularIntensity");
		mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
		mULCViewProjectionMatrix = mProgram->getUniformLocation(
				"uViewProjectionMatrix");
		mULCColorPicking = mProgram->getUniformLocation("uColorPicking");
		mULCPainterColor = mProgram->getUniformLocation("uPainterColor");
	}
	/* Occlusion program */
	if (mProgramOQ) {
		mULCMVPOcclusion = mProgramOQ->getUniformLocation("uMVP");
	}

	/* Shadow program */
	if (mProgramShadow) {
		mULCMVPShadow = mProgramShadow->getUniformLocation("uMVP");
	}

	/* ShadowColor program */
	if (mProgramShadowColor) {
		mULCMVPShadowColor = mProgramShadowColor->getUniformLocation("uMVP");
		mULCModelMatrixShadowColor = mProgramShadowColor->getUniformLocation(
				"uModelMatrix");
	}

	/* AmbientOcclusion programs */
	if (mProgramAOGeometry) {
		mULCMVPAmbientOcclusion = mProgramAOGeometry->getUniformLocation("uMVP");
		mULCPositionAmbientOcclusion = mProgramAOGeometry->getUniformLocation(
				"uMVPosition");
	}

	if (mProgramAOColor) {
		mULCSampleRadius = mProgramAOColor->getUniformLocation("uSampleRadius");
		mULCProjectionMatrix = mProgramAOColor->getUniformLocation("uP");
	}
}

inline void Mesh::initBuffers() {
	if (mIBO) {
		FLOG_INFO("RELOAD IBO");
		mIBO->reload();
	}
	if (mVBO) {
		FLOG_INFO("RELOAD VBO");
		mVBO->reload();
	}
}

inline void Mesh::initVAO() {
	mSampler->bind();

	mVAO->bind();

	mVBO->bind();
	mVBO->attributesSetForVAO();
	mVBO->setReady();
	mVBO->send();

	if (mIBO) {
		mIBO->bind();
		mIBO->setReady();
		mIBO->send();
	}

	mVAO->unbind();
}

inline void Mesh::initVBO() {
	mVBO->getAttributes(mProgram->getHandle());
	mVBO->attributesBind(mProgram);
	mOcclusionMatrix = glm::scale(glm::mat4(1.0f), mVBO->getOcclusionBoxSize());
}

void Mesh::log() {
	mVBO->log();
}

} /* models */
} /* fillwave */
