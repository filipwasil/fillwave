/*
 * Skybox.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: filip
 */

#include <fillwave/models/Skybox.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/models/shapes/SphereSkybox.h>
#include <fillwave/Fillwave.h>

FLOGINIT("Skybox", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Skybox::Skybox(Engine* engine, pTexture3D texture)
		: Reloadable(engine), mTexture(texture) {

	ProgramLoader loader(engine);

	mProgram = loader.getSkybox();
	mProgramDR = loader.getSkyboxDR();

	SphereSkybox sphere(1.0, 10, 10);

	std::vector<GLuint> indices = sphere.getIndices();
	std::vector<core::VertexPosition> vertices = sphere.getVertices();

	FLOG_DEBUG("Initializing skybox buffer");

	mIBO = pIndexBufferBasic(new core::IndexBufferBasic(indices));
	mVBO = pVertexBufferPosition(new core::VertexBufferPosition(vertices));

	initPipeline();
	initVBO();
	initVAO();
	initUniformsCache();
}

void Skybox::draw(ICamera& camera) {
	mProgram->use();

	core::Uniform::push(mULCCameraPosition, camera.getTranslation());
	core::Uniform::push(mULCModelMatrixPosition, mPhysicsMMC);
	core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
	core::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);

	mVAO->bind();

	mTexture->bind(FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used

	glFrontFace(GL_CW);
	if (mIBO) {
		/* Perform index drawing */
		glDrawElements(
		GL_TRIANGLES, mIBO->getElements(),
		GL_UNSIGNED_INT, (GLvoid*) 0);
	} else {
		/* Perform array drawing */
		glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());
	}
	glFrontFace(GL_CCW);

	core::Texture2D::unbind2DTextures();

	mVAO->unbind();
	core::Program::disusePrograms();
}

void Skybox::drawDR(ICamera& camera) {
	mProgramDR->use();

	core::Uniform::push(mULCCameraPosition, camera.getTranslation());
	core::Uniform::push(mULCModelMatrixPosition, mPhysicsMMC);
	core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
	core::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);

	mVAO->bind();

	mTexture->bind(FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used

	glFrontFace(GL_CW);
	if (mIBO) {
		/* Perform index drawing */
		glDrawElements(
		GL_TRIANGLES, mIBO->getElements(),
		GL_UNSIGNED_INT, (GLvoid*) 0);
	} else {
		/* Perform array drawing */
		glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());
	}
	glFrontFace(GL_CCW);

	core::Texture2D::unbind2DTextures();

	mVAO->unbind();
	core::Program::disusePrograms();
}

inline void Skybox::initBuffers() {
	if (mIBO) {
		mIBO->reload();
	}
	if (mVBO) {
		mVBO->reload();
	}
}

inline void Skybox::initPipeline() {

}

inline void Skybox::initUniformsCache() {
	mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
	mULCModelMatrixPosition = mProgram->getUniformLocation("uModelMatrix");
	mULCViewProjectionMatrix = mProgram->getUniformLocation(
			"uViewProjectionMatrix");
	mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
}

inline void Skybox::initVAO() {
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

inline void Skybox::initVBO() {
	mVBO->getAttributes(mProgram->getHandle());
	mVBO->attributesBind(mProgram);
}

pSkybox buildSkybox(Engine* engine, pTexture3D texture) {
	return std::make_shared<framework::Skybox>(engine, texture);
}

} /* framework */
} /* fillwave */
