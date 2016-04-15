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

Skybox::Skybox(Engine* engine, core::Texture3D* texture) :
	IReloadable(engine), mTexture(texture) {

	ProgramLoader loader(engine);

	mProgram = loader.getSkybox();
	mProgramDR = loader.getSkyboxDR();

	SphereSkybox sphere(1.0, 10, 10);

	std::vector<GLuint> indices = sphere.getIndices();
	std::vector<core::VertexPosition> vertices = sphere.getVertices();

	FLOG_DEBUG("Initializing skybox buffer");

	mIBO = engine->storeBuffer<core::IndexBuffer>(mVAO, indices);
	mVBO = engine->storeBuffer<core::VertexBufferPosition>(mVAO, vertices);

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

	mTexture->bind(
	   FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used

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

	core::VertexArray::unbindVAO();
	core::Program::disusePrograms();
}

void Skybox::drawDR(ICamera& camera) {
	mProgramDR->use();

	core::Uniform::push(mULCCameraPosition, camera.getTranslation());
	core::Uniform::push(mULCModelMatrixPosition, mPhysicsMMC);
	core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
	core::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);

	mVAO->bind();

	mTexture->bind(
	   FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used

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

	core::VertexArray::unbindVAO();
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
	mVBO->setLoaded(GL_FALSE);
	mVBO->send();
	if (mIBO) {
		mIBO->bind();
		mIBO->setLoaded(GL_FALSE);
		mIBO->send();
	}
	core::VertexArray::unbindVAO();
}

inline void Skybox::initVBO() {
	mVBO->initAttributes(mProgram->getHandle());
}

bool Skybox::getRenderItem(RenderItem& item) {
	item.mCount = mIBO ? mIBO->getElements() : mVBO->getElements();
	item.mDataType = GL_UNSIGNED_INT;
	item.mFirst = 0;
	item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
	item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
	item.mHandles[RenderItem::eRenderHandleVAO] = mVAO->getHandle();
	item.mHandles[RenderItem::eRenderHandleDiffuse] =
	   mTexture->getHandle(); //xxx 3d texture handle
	item.mIndicesPointer = 0;
	item.mMode = GL_TRIANGLES;
	item.mRenderStatus = mIBO ? 0xe0 :
	                     0xa0; // vao, ibo, diff, norm, spec, blend, cont, anim
	return true;
}

} /* framework */
pSkybox buildSkybox(Engine* engine, core::Texture3D* texture) {
	return std::make_shared < framework::Skybox > (engine, texture);
}
} /* fillwave */
