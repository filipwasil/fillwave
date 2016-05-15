/*
 * RendererDR.cpp
 *
 *  Created on: Jan 5, 2016
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <fillwave/renderers/RendererDR.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/Skybox.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>
#include <fillwave/common/Macros.h>
#include <fillwave/management/LightSystem.h>
#include <fillwave/Log.h>

#if defined(FILLWAVE_GLES_3_0)
#else

FLOGINIT_DEFAULT()

namespace fillwave {
namespace framework {

RendererDR::RendererDR(Engine* engine, ProgramLoader& loader)
	:
	mScreenSize(engine->getScreenSize()),
	mLights(engine->getLightSystem()),
	mTextures(engine->getTextureSystem()),
	mProgramMain(loader.getDefaultDR()),
	mProgramMainAnimated(loader.getDefaultBonesDR()),
	mProgramDirecionalLight(loader.getDRDirectionalLights()),
	mProgramSpotLight(loader.getDRSpotLights()),
	mProgramPointLight(loader.getDRPointLights()),
	mProgramDepthless(loader.getDRDepthless()),
	mProgramAmbient(loader.getDRAmbient()),
	mProgramAOGeometry(loader.getAmbientOcclusionGeometry()),
	mProgramAOColor(loader.getAmbientOcclusionColor()),
	mAOGeometryBuffer(engine->storeTextureRenderable()),
	mAOColorBuffer(engine->storeTextureRenderable()),
	mIsAO(GL_FALSE),
	mDeferredColorAttachments(5),
	mDeferredDepthAttachments(1),
	mGBuffer(
	  std::make_unique<core::FramebufferGeometry>(mTextures, mScreenSize[0],
	        mScreenSize[1], mDeferredColorAttachments,
	        mDeferredDepthAttachments)) {

	framework::Sphere sphere(3.0f, 10.0f,
	                         10.0f); // xxx hardcoded values fix ! todo !
	std::vector<core::VertexBasic> vertices = sphere.getVertices();
	std::vector<GLuint> indices = sphere.getIndices();

	core::VertexArray* vao = new core::VertexArray();
	mDeferredPointLight = std::make_unique<Mesh>(engine, Material(),
	                      nullptr,
	                      nullptr, nullptr,
	                      mProgramPointLight, nullptr, nullptr, loader.getOcclusionQuery(),
	                      nullptr, nullptr, mLights,
	                      engine->storeBuffer<core::VertexBufferBasic>(vao, vertices),
	                      engine->storeBuffer<core::IndexBuffer>(vao, indices),
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	                      nullptr,
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
	                      GL_TRIANGLES, vao);

	initUniforms();
	initGeometryBuffer();
	initGeometryShading();
	initUniformsCache();

	reset(mScreenSize[0], mScreenSize[1]);
}

void RendererDR::update(IRenderable* renderable) {
	RenderItem item;
	renderable->getRenderItem(item);
	item.mStatus.bIsAnimated ? mAnimatedNodes.push_back(renderable) :
	mNodes.push_back(renderable);
}

void RendererDR::draw(ICamera& camera) {
	mGBuffer->setAttachments(); //bind for geom pass
	drawGeometryPass(camera);
//	drawAOPass(camera);
	drawColorPass(camera);
	drawDebug();
}

void RendererDR::reset(GLuint width, GLuint height) {

	mFlagReload = true;

	mScreenSize = glm::vec2(width, height);

	mGBuffer->resize(mScreenSize[0], mScreenSize[1]);

	mProgramSpotLight->use();
	core::Uniform::push(mULCScreenSizeSpot,
	                    glm::vec2(mScreenSize[0], mScreenSize[1]));

	mProgramDirecionalLight->use();
	core::Uniform::push(mULCScreenSizeDirectional,
	                    glm::vec2(mScreenSize[0], mScreenSize[1]));

	mProgramPointLight->use();
	core::Uniform::push(mULCScreenSizePoint,
	                    glm::vec2(mScreenSize[0], mScreenSize[1]));

	mProgramDepthless->use();
	core::Uniform::push(mULCDRScreenSize,
	                    glm::vec2(mScreenSize[0], mScreenSize[1]));

	mProgramAmbient->use();
	core::Uniform::push(mULCDRAScreenSize,
	                    glm::vec2(mScreenSize[0], mScreenSize[1]));
}

void RendererDR::clear() {

	mFlagReload = true;

	size_t predictedSize = mNodes.size() + 1;
	mNodes.clear();
	mNodes.reserve(predictedSize);

	size_t predictedSizeA = mAnimatedNodes.size() + 1;
	mAnimatedNodes.clear();
	mAnimatedNodes.reserve(predictedSizeA);
}

inline void RendererDR::drawGeometryPass(ICamera& camera) {
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	mProgramMain->use();
	for (auto& node : mNodes) {
		node->drawDR(camera);
	}

	mProgramMainAnimated->use();
	for (auto& node : mAnimatedNodes) {
		node->drawDR(camera);
	}

	glDepthMask(GL_FALSE);
}

inline void RendererDR::drawAOPass(ICamera& camera) {
	mAOGeometryBuffer->bindForWriting();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mProgramAOGeometry->use();
	for (auto& node : mNodes) {
		node->drawAOG(camera);
	}
	for (auto& node : mAnimatedNodes) {
		node->drawAOG(camera);
	}

	mAOColorBuffer->bindForWriting();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mAOGeometryBuffer->bind(FILLWAVE_POSITION_ATTACHMENT);

	mProgramAOColor->use();
	for (auto& node : mNodes) {
		node->drawAOC(camera);
	}
	for (auto& node : mAnimatedNodes) {
		node->drawAOC(camera);
	}
}

inline void RendererDR::drawColorPassBegin() {
	mGBuffer->setAttachments();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	mGBuffer->setAttachmentSummaryForWriting();
	mGBuffer->bindAttachments();
}

inline void RendererDR::drawColorPass(ICamera& camera) {
	drawColorPassBegin();
	drawAmbientPass();
	drawDepthlessPass();

	GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;

	mAOColorBuffer->bind(FILLWAVE_AO_UNIT);

	drawLightsSpotPass(camera, currentTextureUnit);
	drawLightsDirectionalPass(camera, currentTextureUnit);
	drawLightsPointPass(camera, currentTextureUnit);

	drawColorPassEnd();
}

inline void RendererDR::drawAmbientPass() {
	mProgramAmbient->use();
	glUniform3fv(mULCAmbient, 1, mAmbientGlobal);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

inline void RendererDR::drawDepthlessPass() {
	mProgramDepthless->use();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

inline void RendererDR::drawLightsSpotPass(ICamera& camera,
      GLint& textureUnit) {
	for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {

		mProgramSpotLight->use();
		mLights->updateDeferredBufferSpot(i, mProgramSpotLight,
		                                  textureUnit++);

		core::Uniform::push(mULCCameraPositionSpot,
		                    camera.getTranslation());
		core::Uniform::push(mULCIsAOSpot, mIsAO ? 1 : 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

inline void RendererDR::drawLightsDirectionalPass(
   ICamera& camera,
   GLint& textureUnit) {
	for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {

		mProgramDirecionalLight->use();
		mLights->updateDeferredBufferDirectional(i,
		      mProgramDirecionalLight, textureUnit++);

		core::Uniform::push(mULCCameraPositionDirectional,
		                    camera.getTranslation());
		core::Uniform::push(mULCIsAODirectional, mIsAO ? 1 : 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

inline void RendererDR::drawLightsPointPass(ICamera& camera,
      GLint& textureUnit) {
	glEnable(GL_STENCIL_TEST);

	for (size_t i = 0; i < mLights->mLightsPoint.size(); i++) {
		// DSStencilPass

		mGBuffer->setAttachmentStencilDepth();

		// Disable color/depth write and enable stencil
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glClear(GL_STENCIL_BUFFER_BIT);
		glDisable(GL_BLEND);

		// We need the stencil test to be enabled but we want it
		// to succeed always. Only the depth test matters.
		glStencilFunc(GL_ALWAYS, 0, 0);

		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

		mProgramPointLight->use();
		mLights->updateDeferredBufferPoint(i, mProgramPointLight,
		                                   textureUnit++);

		core::Uniform::push(mULCCameraPositionPoint, camera.getTranslation());
		core::Uniform::push(mULCMVPPoint,
		                    camera.getViewProjection()
		                    * glm::translate(glm::mat4(1.0),
		                                     mLights->mLightsPoint[i]->getTranslation()));

		core::Uniform::push(mULCIsAOPoint, mIsAO ? 1 : 0);
//xxx      if runtime changing is not needed
//      if (mIsAO) {
//         core::Uniform::push(mULCIsAOPoint, 1);
//      }

		mDeferredPointLight->drawFast(camera);

		//BindForLightPass
		mGBuffer->setAttachmentSummaryForWriting();
		mGBuffer->bindAttachments();

		//draw regular
		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		mDeferredPointLight->drawFast(camera);

		glCullFace(GL_BACK);
		glDisable(GL_BLEND);
	}

	glDisable(GL_STENCIL_TEST);
}

inline void RendererDR::drawColorPassEnd() {
	mGBuffer->setAttachmentSummaryForReading();
	glBlitFramebuffer(0, 0, mScreenSize[0], mScreenSize[1], 0, 0, mScreenSize[0],
	                  mScreenSize[1],
	                  GL_COLOR_BUFFER_BIT,
	                  GL_LINEAR);
}

inline void RendererDR::initUniforms() {
	mProgramDirecionalLight->use();
	mProgramDirecionalLight->uniformPush("uWorldPositionAttachment",
	                                     FILLWAVE_POSITION_ATTACHMENT);
	mProgramDirecionalLight->uniformPush("uDiffuseTexelAttachment",
	                                     FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramDirecionalLight->uniformPush("uNormalAttachment",
	                                     FILLWAVE_NORMAL_ATTACHMENT);
	mProgramDirecionalLight->uniformPush("uSpecularTexelAttachment",
	                                     FILLWAVE_SPECULAR_ATTACHMENT);
	mProgramDirecionalLight->uniformPush("uScreenSize", mScreenSize);
	mProgramDirecionalLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

	mProgramSpotLight->use();
	mProgramSpotLight->uniformPush("uWorldPositionAttachment",
	                               FILLWAVE_POSITION_ATTACHMENT);
	mProgramSpotLight->uniformPush("uDiffuseTexelAttachment",
	                               FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramSpotLight->uniformPush("uNormalAttachment",
	                               FILLWAVE_NORMAL_ATTACHMENT);
	mProgramSpotLight->uniformPush("uSpecularTexelAttachment",
	                               FILLWAVE_SPECULAR_ATTACHMENT);
	mProgramSpotLight->uniformPush("uScreenSize", mScreenSize);
	mProgramSpotLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

	mProgramPointLight->use();
	mProgramPointLight->uniformPush("uWorldPositionAttachment",
	                                FILLWAVE_POSITION_ATTACHMENT);
	mProgramPointLight->uniformPush("uDiffuseTexelAttachment",
	                                FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramPointLight->uniformPush("uNormalAttachment",
	                                FILLWAVE_NORMAL_ATTACHMENT);
	mProgramPointLight->uniformPush("uSpecularTexelAttachment",
	                                FILLWAVE_SPECULAR_ATTACHMENT);
	mProgramPointLight->uniformPush("uScreenSize", mScreenSize);
	mProgramPointLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

	mProgramDepthless->use();
	mProgramDepthless->uniformPush("uWorldPositionAttachment",
	                               FILLWAVE_POSITION_ATTACHMENT);
	mProgramDepthless->uniformPush("uDiffuseTexelAttachment",
	                               FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramDepthless->uniformPush("uScreenSize", mScreenSize);

	mProgramAmbient->use();
	mProgramAmbient->uniformPush("uDiffuseTexelAttachment",
	                             FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramAmbient->uniformPush("uScreenSize", mScreenSize);
}

inline void RendererDR::initUniformsCache() {
	mULCAmbient = mProgramSpotLight->getUniformLocation(
	                 "uAmbient");

	mULCCameraPositionSpot = mProgramSpotLight->getUniformLocation(
	                            "uCameraPosition");
	mULCAmbientIntensitySpot = mProgramSpotLight->getUniformLocation(
	                              "uLight.base.ambientIntensity");
	mULCScreenSizeSpot = mProgramSpotLight->getUniformLocation("uScreenSize");
	mULCShadowUnitSpot = mProgramSpotLight->getUniformLocation("uShadowUnit");
	mULCIsAOSpot = mProgramSpotLight->getUniformLocation("uIsAO");

	mULCCameraPositionDirectional =
	   mProgramDirecionalLight->getUniformLocation("uCameraPosition");
	mULCAmbientIntensityDirectional =
	   mProgramDirecionalLight->getUniformLocation("uAmbientIntensity");
	mULCScreenSizeDirectional = mProgramDirecionalLight->getUniformLocation(
	                               "uScreenSize");
	mULCShadowUnitDirectional = mProgramDirecionalLight->getUniformLocation(
	                               "uShadowUnit");
	mULCIsAODirectional = mProgramDirecionalLight->getUniformLocation("uIsAO");

	mULCCameraPositionPoint = mProgramPointLight->getUniformLocation(
	                             "uCameraPosition");
	mULCMVPPoint = mProgramPointLight->getUniformLocation("uMVP");
	mULCScreenSizePoint = mProgramPointLight->getUniformLocation(
	                         "uScreenSize");
	mULCShadowUnitPoint = mProgramPointLight->getUniformLocation(
	                         "uShadowUnit");
	mULCIsAOPoint = mProgramSpotLight->getUniformLocation("uIsAO");

	mULCDRDepthlesDiffuseTexel = mProgramDepthless->getUniformLocation(
	                                "uDiffuseTexelAttachment");
	mULCDRDepthlessPositionTexel = mProgramDepthless->getUniformLocation(
	                                  "uWorldPositionAttachment");
	mULCDRScreenSize = mProgramDepthless->getUniformLocation("uScreenSize");

	mULCDRAScreenSize = mProgramAmbient->getUniformLocation("uScreenSize");
	mULCDRADiffuseAttachment = mProgramAmbient->getUniformLocation(
	                              "uDiffuseTexelAttachment");
}

inline void RendererDR::initGeometryBuffer() {
	GLint maxAttach = 0, maxDrawBuf = 0;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttach);
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuf);

	if (glm::max(maxAttach, maxDrawBuf) > static_cast<GLint>
	      (mDeferredColorAttachments)) {
		//xxx todo remove this function
	}
}

inline void RendererDR::initGeometryShading() {
	GLint MaxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
	FLOG_DEBUG("Max supported patch vertices %d\n", MaxPatchVertices);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
}

inline void RendererDR::drawDebug() {
	GLuint w = mScreenSize[0];
	GLuint h = mScreenSize[1];
	GLuint debugAttachmentScreens[4][4] = { {0, 0, w / 2, h / 2}, // position
		{	0, h / 2, w / 2, h},     // color
		{	w / 2, h / 2, w, h}, // normal
		{	w / 2, 0, w, h / 2}       // specular
	};

	/* Move to right up corner*/
	for (int i = 0; i < 4; i++) {
		debugAttachmentScreens[i][0] = (debugAttachmentScreens[i][0] + w) / 2;
		debugAttachmentScreens[i][1] = (debugAttachmentScreens[i][1] + h)
		                               / 2;
		debugAttachmentScreens[i][2] = (debugAttachmentScreens[i][2] + w) / 2;
		debugAttachmentScreens[i][3] = (debugAttachmentScreens[i][3] + h)
		                               / 2;
	}

	core::Framebuffer::bindScreenFramebufferForWriting();
	for (GLuint i = 0; i < mDeferredColorAttachments; i++) {
		mGBuffer->bindForReading(); /* We will bind GBuffer for reading ...*/
		mGBuffer->setReadColorAttachment(
		   i); /* ... and take color attachment color i 0 (out location 0 from fragment shader) ... */
		glBlitFramebuffer(0, 0, w, h, debugAttachmentScreens[i][0],
		                  debugAttachmentScreens[i][1], debugAttachmentScreens[i][2],
		                  debugAttachmentScreens[i][3],
		                  GL_COLOR_BUFFER_BIT,
		                  GL_LINEAR); /* ... to finally copy it into main framebuffer */
	}
	core::Framebuffer::bindScreenFramebuffer();
}

} /* namespace framework */
} /* namespace fillwave */

#endif /* defined(FILLWAVE_GLES_3_0) */
