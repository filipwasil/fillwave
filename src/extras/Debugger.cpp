/*
 * Debugger.cpp
 *
 *  Created on: Jul 26, 2014
 *      Author: filip
 */

#include <fillwave/Fillwave.h>

#include <fillwave/core/buffers/VertexBufferDebug.h>
#include <fillwave/core/rendering/FramebufferGeometry.h>

#include <fillwave/extras/Debugger.h>

#include <fillwave/space/Camera.h>

#include <fillwave/management/LightManager.h>

#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/extras/Log.h>

namespace fillwave {

FLOGINIT("Debugger", FERROR | FFATAL | FINFO)

Debugger::Debugger(Engine* engine)
		:
				Reloadable(engine),
				mState(eDebuggerState::off),
				mEngine(engine),
				mVBO(pVertexBufferDebug(new core::VertexBufferDebug(1.0))),
				mMiniwindowSize(1.0 / 6.0),
				mMiniwindowsOccupied(0) {

	loader::ProgramLoader loader;

	mProgram = loader.getDebugger(engine);

	initPipeline();
	initVBO();
	initVAO();
	initUniformsCache();
}

void Debugger::setState(eDebuggerState state) {
	if (state == eDebuggerState::toggleState) {
		switch (mState) {
			case eDebuggerState::lightsSpot:
				mState = eDebuggerState::lightsSpotDepth;
				break;
			case eDebuggerState::lightsSpotDepth:
				mState = eDebuggerState::lightsSpotColor;
				break;
			case eDebuggerState::lightsSpotColor:
				mState = eDebuggerState::lightsPoint;
				break;
			case eDebuggerState::lightsPoint:
				mState = eDebuggerState::lightsPointDepth;
				break;
			case eDebuggerState::lightsPointDepth:
				mState = eDebuggerState::lightsPointColor;
				break;
			case eDebuggerState::lightsPointColor:
				mState = eDebuggerState::pickingMap;
				break;
			case eDebuggerState::pickingMap:
				mState = eDebuggerState::off;
				break;
			case eDebuggerState::off:
				mState = eDebuggerState::lightsSpot;
				break;
			default:
				break;
		}
	} else {
		mState = state;
	}
}

eDebuggerState Debugger::getState() {
	return mState;
}

void Debugger::setMiniwindowSize(GLfloat size) {
	mMiniwindowSize = size;
}

void Debugger::renderFromCamera(space::Camera& c, GLint id) {
	glViewport(mEngine->getScreenSize()[0] * (id) * mMiniwindowSize,
			mEngine->getScreenSize()[1] * (1.0f - mMiniwindowSize),
			mEngine->getScreenSize()[0] * mMiniwindowSize,
			mEngine->getScreenSize()[1] * mMiniwindowSize);

	glClear(GL_DEPTH_BUFFER_BIT);

	mEngine->getCurrentScene()->drawFromCustomCamera(c);

	glViewport(0, 0, mEngine->getScreenSize()[0], mEngine->getScreenSize()[1]);
}

void Debugger::renderPickingMap() {
	glViewport(mEngine->getScreenSize()[0] * (1.0f - mMiniwindowSize), 0,
			mEngine->getScreenSize()[0] * mMiniwindowSize,
			mEngine->getScreenSize()[1] * mMiniwindowSize);

	glClear(GL_DEPTH_BUFFER_BIT);
	mEngine->getCurrentScene()->drawPicking();
	glViewport(0, 0, mEngine->getScreenSize()[0], mEngine->getScreenSize()[1]);
}

void Debugger::renderDepthOrthographic(GLint id) { //xxx ujednolicić to całe lightID żeby można było usuwać światła
	glViewport(mEngine->getScreenSize()[0] * (id) * mMiniwindowSize, 0,
			mEngine->getScreenSize()[0] * mMiniwindowSize,
			mEngine->getScreenSize()[1] * mMiniwindowSize);

	glClear(GL_DEPTH_BUFFER_BIT);

	mProgram->use();

	mVAO->bind();

	pLightDirectional light = mEngine->getLightManager()->getLightDirectional(
			id - mEngine->getLightManager()->getLightsSpotHowMany());

	space::Camera* cam = light->getShadowCamera().get();

	light->getShadowTexture()->bind(GLint(FILLWAVE_SHADOW_FIRST_UNIT + id));

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	core::Uniform::push(mULCTextureUnit, id);
	core::Uniform::push(mULCNearPlane, cam->getProjectionNearPlane());
	core::Uniform::push(mULCFarPlane, cam->getProjectionFarPlane());

	glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	core::Texture2D::unbind2DTextures();
	mVAO->unbind();
	core::Program::disusePrograms();

	glViewport(0, 0, mEngine->getScreenSize()[0], mEngine->getScreenSize()[1]);
}

void Debugger::renderDepthPerspective(GLint id) { //xxx ujednolicić to całe lightID żeby można było usuwać światła
	glViewport(mEngine->getScreenSize()[0] * (id) * mMiniwindowSize, 0,
			mEngine->getScreenSize()[0] * mMiniwindowSize,
			mEngine->getScreenSize()[1] * mMiniwindowSize);

	glClear(GL_DEPTH_BUFFER_BIT);

	mProgram->use();

	mVAO->bind();

	pLightSpot light = mEngine->getLightManager()->getLightSpot(id);

	space::CameraPerspective cam = *(light->getShadowCamera().get());

	light->getShadowTexture()->bind(GLint(FILLWAVE_SHADOW_FIRST_UNIT + id));

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	core::Uniform::push(mULCTextureUnit, id);
	core::Uniform::push(mULCNearPlane, cam.getProjectionNearPlane());
	core::Uniform::push(mULCFarPlane, cam.getProjectionFarPlane());

	glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	core::Texture2D::unbind2DTextures();
	mVAO->unbind();
	core::Program::disusePrograms();

	glViewport(0, 0, mEngine->getScreenSize()[0], mEngine->getScreenSize()[1]);
}

void Debugger::renderGeometryBuffer(
		GLuint width,
		GLuint height,
		GLuint attachments,
		core::FramebufferGeometry* buffer) {
	GLuint debugAttachmentScreens[4][4] = { { 0, 0, width / 2, height / 2 }, // position
			{ 0, height / 2, width / 2, height },     // color
			{ width / 2, height / 2, width, height }, // normal
			{ width / 2, 0, width, height / 2 }       // specular
	};

	/* Move to right up corner*/
	for (int i = 0; i < 4; i++) {
		debugAttachmentScreens[i][0] = (debugAttachmentScreens[i][0] + width) / 2;
		debugAttachmentScreens[i][1] = (debugAttachmentScreens[i][1] + height)
				/ 2;
		debugAttachmentScreens[i][2] = (debugAttachmentScreens[i][2] + width) / 2;
		debugAttachmentScreens[i][3] = (debugAttachmentScreens[i][3] + height)
				/ 2;
	}

	core::Framebuffer::bindScreenFramebufferForWriting();
	for (GLuint i = 0; i < attachments; i++) {
		buffer->bindForReading(); /* We will bind GBuffer for reading ...*/
		buffer->setReadColorAttachment(i); /* ... and take color attachment color i 0 (out location 0 from fragment shader) ... */
		glBlitFramebuffer(0, 0, width, height, debugAttachmentScreens[i][0],
				debugAttachmentScreens[i][1], debugAttachmentScreens[i][2],
				debugAttachmentScreens[i][3],
				GL_COLOR_BUFFER_BIT,
				GL_LINEAR); /* ... to finally copy it into main framebuffer */
	}
	core::Framebuffer::bindScreenFramebuffer();
}

inline void Debugger::initBuffers() {
	if (mVBO) {
		mVBO->reload();
	}
}

inline void Debugger::initPipeline() {

}

inline void Debugger::initUniformsCache() {
	mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
	mULCNearPlane = mProgram->getUniformLocation("uNearplane");
	mULCFarPlane = mProgram->getUniformLocation("uFarPlane");
}

inline void Debugger::initVAO() {
	mSampler->bind();
	mVAO->bind();

	mVBO->bind();
	mVBO->setReady();
	mVBO->send();
	mVBO->attributesSetForVAO();

	mVAO->unbind();
}

inline void Debugger::initVBO() {
	mVBO->getAttributes(mProgram->getHandle());
	mVBO->attributesBind(mProgram);
}

} /* fillwave */

