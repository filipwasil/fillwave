/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/flc/renderers/RendererDR.h>
#include <flw/flf/models/Skybox.h>
#include <flw/flf/loaders/ProgramLoader.h>
#include <flw/Fillwave.h>
#include <flw/flf/management/LightSystem.h>
#include <flw/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flc {

RendererDR::RendererDR(Engine *engine, flf::ProgramLoader &loader)
  : mScreenSize(engine->getScreenSize())
  , mLights(engine->getLightSystem())
  , mTextures(engine->getTextureSystem())
  , mProgramMain(loader.getProgram(EProgram::basicDR))
  , mProgramMainAnimated(loader.getProgram(EProgram::basicAnimatedDR))
  , mProgramDirectionalLight(loader.getProgram(EProgram::directionalLightsDR))
  , mProgramSpotLight(loader.getProgram(EProgram::spotLightsDR))
  , mProgramPointLight(loader.getProgram(EProgram::pointLightsDR))
  , mProgramDepthless(loader.getProgram(EProgram::depthlessDR))
  , mProgramAmbient(loader.getProgram(EProgram::ambientDR))
  , mProgramAOGeometry(loader.getProgram(EProgram::ambientOcclusionGeometry))
  , mProgramAOColor(loader.getProgram(EProgram::ambientOcclusionColor))
  , mAOGeometryBuffer(engine->storeTextureRenderable())
  , mAOColorBuffer(engine->storeTextureRenderable())
  , mIsAO(GL_FALSE)
  , mDeferredColorAttachments(5)
  , mGBuffer(std::make_unique<FramebufferGeometry>(mTextures,
                                                        mScreenSize[0],
                                                        mScreenSize[1],
                                                        mDeferredColorAttachments)) {
  //todo RendererDR not ready
  flf::Sphere sphere(3.0f, 10, 10); //xxx hardcoded values fix ! todo !
  auto vertices = sphere.getVertices();
  auto indices = sphere.getIndices();

  auto vao = new VertexArray();
  mDeferredPointLight = std::make_unique<flf::Mesh>(engine,
                                               Material(),
                                               nullptr,
                                               nullptr,
                                               nullptr,
                                               mProgramPointLight,
                                               nullptr,
                                               nullptr,
                                               loader.getProgram(EProgram::occlusionQuery),
                                               nullptr,
                                               nullptr,
                                               mLights,
                                               vao,
                                               false,
                                               engine->storeBuffer<VertexBufferBasic>(vao, vertices),
                                               engine->storeBuffer<IndexBuffer>(vao, indices),
                                               nullptr,
                                               GL_TRIANGLES);

  initUniforms();
  initGeometryBuffer();
  initGeometryShading();
  initUniformsCache();

  reset(mScreenSize.x, mScreenSize.y);
}

void RendererDR::update(IRenderable *renderable) {
  RenderItem item;
  renderable->getRenderItem(item);
  item.mStatus.bIsAnimated ? mAnimatedNodes.push_back(renderable) : mNodes.push_back(renderable);
}

void RendererDR::draw(ICamera &camera) {
  mGBuffer->setAttachments(); //bind for geom pass
  drawGeometryPass(camera);
//	drawAOPass(camera);
  drawColorPass(camera);
  drawDebug();
}

void RendererDR::reset(GLuint width, GLuint height) {
  mFlagReload = true;

  mScreenSize = {
    width,
    height
  };

  mGBuffer->resize(width, height);

  const glm::vec2 screenSizeF(mScreenSize);

  mProgramSpotLight->use();
  Uniform::push(mULCScreenSizeSpot, screenSizeF);

  mProgramDirectionalLight->use();
  Uniform::push(mULCScreenSizeDirectional, screenSizeF);

  mProgramPointLight->use();
  Uniform::push(mULCScreenSizePoint, screenSizeF);

  mProgramDepthless->use();
  Uniform::push(mULCDRScreenSize, screenSizeF);

  mProgramAmbient->use();
  Uniform::push(mULCDRAScreenSize, screenSizeF);
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

inline void RendererDR::drawGeometryPass(ICamera &camera) {
  glDepthMask(GL_TRUE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  mProgramMain->use();
  for (auto &node : mNodes) {
    node->drawDR(camera);
  }

  mProgramMainAnimated->use();
  for (auto &node : mAnimatedNodes) {
    node->drawDR(camera);
  }

  glDepthMask(GL_FALSE);
}

inline void RendererDR::drawAOPass(ICamera &camera) {
  mAOGeometryBuffer->bindForWriting();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  mProgramAOGeometry->use();
  for (auto &node : mNodes) {
    node->drawAOG(camera);
  }
  for (auto &node : mAnimatedNodes) {
    node->drawAOG(camera);
  }

  mAOColorBuffer->bindForWriting();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  mAOGeometryBuffer->mTexture2D.bind(FILLWAVE_POSITION_ATTACHMENT);

  mProgramAOColor->use();
  for (auto &node : mNodes) {
    node->drawAOC(camera);
  }
  for (auto &node : mAnimatedNodes) {
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

inline void RendererDR::drawColorPass(ICamera &camera) {
  drawColorPassBegin();
  drawAmbientPass();
  drawDepthlessPass();

  GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;

  mAOColorBuffer->mTexture2D.bind(FILLWAVE_AO_UNIT);

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

inline void RendererDR::drawLightsSpotPass(ICamera &camera, GLint &textureUnit) {
  for (size_t i = 0; i < mLights.mLightsSpot.size(); i++) {

    mProgramSpotLight->use();
    mLights.updateDeferredBufferSpot(i, mProgramSpotLight, textureUnit++);

    Uniform::push(mULCCameraPositionSpot, camera.getTranslation());
    Uniform::push(mULCIsAOSpot, mIsAO ? 1 : 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }
}

inline void RendererDR::drawLightsDirectionalPass(ICamera &camera, GLint &textureUnit) {
  for (size_t i = 0; i < mLights.mLightsDirectional.size(); i++) {

    mProgramDirectionalLight->use();
    mLights.updateDeferredBufferDirectional(i, mProgramDirectionalLight, textureUnit++);

    Uniform::push(mULCCameraPositionDirectional, camera.getTranslation());
    Uniform::push(mULCIsAODirectional, mIsAO ? 1 : 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }
}

inline void RendererDR::drawLightsPointPass(ICamera &camera, GLint &textureUnit) {
  glEnable(GL_STENCIL_TEST);

  for (size_t i = 0; i < mLights.mLightsPoint.size(); i++) {
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
    mLights.updateDeferredBufferPoint(i, mProgramPointLight, textureUnit++);

    Uniform::push(mULCCameraPositionPoint, camera.getTranslation());
    Uniform::push(mULCMVPPoint,
                       camera.getViewProjection() *
                       glm::translate(glm::mat4(1.0), mLights.mLightsPoint[i]->getTranslation()));

    Uniform::push(mULCIsAOPoint, mIsAO ? 1 : 0);
//xxx      if runtime changing is not needed
//      if (mIsAO) {
//         Uniform::push(mULCIsAOPoint, 1);
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
  glBlitFramebuffer(0,
                    0,
                    mScreenSize[0],
                    mScreenSize[1],
                    0,
                    0,
                    mScreenSize[0],
                    mScreenSize[1],
                    GL_COLOR_BUFFER_BIT,
                    GL_LINEAR);
}

inline void RendererDR::initUniforms() {
  mProgramDirectionalLight->use();
  mProgramDirectionalLight->uniformPush("uWorldPositionAttachment", FILLWAVE_POSITION_ATTACHMENT);
  mProgramDirectionalLight->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
  mProgramDirectionalLight->uniformPush("uNormalAttachment", FILLWAVE_NORMAL_ATTACHMENT);
  mProgramDirectionalLight->uniformPush("uSpecularTexelAttachment", FILLWAVE_SPECULAR_ATTACHMENT);
  mProgramDirectionalLight->uniformPush("uScreenSize", mScreenSize);
  mProgramDirectionalLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

  mProgramSpotLight->use();
  mProgramSpotLight->uniformPush("uWorldPositionAttachment", FILLWAVE_POSITION_ATTACHMENT);
  mProgramSpotLight->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
  mProgramSpotLight->uniformPush("uNormalAttachment", FILLWAVE_NORMAL_ATTACHMENT);
  mProgramSpotLight->uniformPush("uSpecularTexelAttachment", FILLWAVE_SPECULAR_ATTACHMENT);
  mProgramSpotLight->uniformPush("uScreenSize", mScreenSize);
  mProgramSpotLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

  mProgramPointLight->use();
  mProgramPointLight->uniformPush("uWorldPositionAttachment", FILLWAVE_POSITION_ATTACHMENT);
  mProgramPointLight->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
  mProgramPointLight->uniformPush("uNormalAttachment", FILLWAVE_NORMAL_ATTACHMENT);
  mProgramPointLight->uniformPush("uSpecularTexelAttachment", FILLWAVE_SPECULAR_ATTACHMENT);
  mProgramPointLight->uniformPush("uScreenSize", mScreenSize);
  mProgramPointLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

  mProgramDepthless->use();
  mProgramDepthless->uniformPush("uWorldPositionAttachment", FILLWAVE_POSITION_ATTACHMENT);
  mProgramDepthless->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
  mProgramDepthless->uniformPush("uScreenSize", mScreenSize);

  mProgramAmbient->use();
  mProgramAmbient->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
  mProgramAmbient->uniformPush("uScreenSize", mScreenSize);
}

inline void RendererDR::initUniformsCache() {
  mULCAmbient = mProgramSpotLight->getUniformLocation("uAmbient");

  mULCCameraPositionSpot = mProgramSpotLight->getUniformLocation("uCameraPosition");
  mULCAmbientIntensitySpot = mProgramSpotLight->getUniformLocation("uLight.base.ambientIntensity");
  mULCScreenSizeSpot = mProgramSpotLight->getUniformLocation("uScreenSize");
  mULCShadowUnitSpot = mProgramSpotLight->getUniformLocation("uShadowUnit");
  mULCIsAOSpot = mProgramSpotLight->getUniformLocation("uIsAO");

  mULCCameraPositionDirectional = mProgramDirectionalLight->getUniformLocation("uCameraPosition");
  mULCAmbientIntensityDirectional = mProgramDirectionalLight->getUniformLocation("uAmbientIntensity");
  mULCScreenSizeDirectional = mProgramDirectionalLight->getUniformLocation("uScreenSize");
  mULCShadowUnitDirectional = mProgramDirectionalLight->getUniformLocation("uShadowUnit");
  mULCIsAODirectional = mProgramDirectionalLight->getUniformLocation("uIsAO");

  mULCCameraPositionPoint = mProgramPointLight->getUniformLocation("uCameraPosition");
  mULCMVPPoint = mProgramPointLight->getUniformLocation("uMVP");
  mULCScreenSizePoint = mProgramPointLight->getUniformLocation("uScreenSize");
  mULCShadowUnitPoint = mProgramPointLight->getUniformLocation("uShadowUnit");
  mULCIsAOPoint = mProgramSpotLight->getUniformLocation("uIsAO");

  mULCDRDepthlesDiffuseTexel = mProgramDepthless->getUniformLocation("uDiffuseTexelAttachment");
  mULCDRDepthlessPositionTexel = mProgramDepthless->getUniformLocation("uWorldPositionAttachment");
  mULCDRScreenSize = mProgramDepthless->getUniformLocation("uScreenSize");

  mULCDRAScreenSize = mProgramAmbient->getUniformLocation("uScreenSize");
  mULCDRADiffuseAttachment = mProgramAmbient->getUniformLocation("uDiffuseTexelAttachment");
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
  fLogD("Max supported patch vertices %d\n", MaxPatchVertices);
  glPatchParameteri(GL_PATCH_VERTICES, 3);
}

inline void RendererDR::drawDebug() {
  GLuint w = static_cast<GLuint>(mScreenSize[0]);
  GLuint h = static_cast<GLuint>(mScreenSize[1]);
  GLuint debugAttachmentScreens[4][4] = {{0,     0,     w / 2, h / 2}, // position
                                         {0,     h / 2, w / 2, h},     // color
                                         {w / 2, h / 2, w,     h},     // normal
                                         {w / 2, 0,     w,     h / 2}  // specular
  };

  /* Move to right up corner*/
  for (int i = 0; i < 4; i++) {
    debugAttachmentScreens[i][0] = (debugAttachmentScreens[i][0] + w) / 2;
    debugAttachmentScreens[i][1] = (debugAttachmentScreens[i][1] + h) / 2;
    debugAttachmentScreens[i][2] = (debugAttachmentScreens[i][2] + w) / 2;
    debugAttachmentScreens[i][3] = (debugAttachmentScreens[i][3] + h) / 2;
  }

  Framebuffer::bindScreenFramebufferForWriting();
  for (GLuint i = 0; i < mDeferredColorAttachments; i++) {
    mGBuffer->bindForReading(); /* We will bind GBuffer for reading ...*/
    mGBuffer->setReadColorAttachment(i); /* ... and take color attachment color i 0 (out location 0 from fragment shader) ... */
    glBlitFramebuffer(0,
                      0,
                      w,
                      h,
                      debugAttachmentScreens[i][0],
                      debugAttachmentScreens[i][1],
                      debugAttachmentScreens[i][2],
                      debugAttachmentScreens[i][3],
                      GL_COLOR_BUFFER_BIT,
                      GL_LINEAR); /* ... to finally copy it into main framebuffer */
  }
  Framebuffer::bindScreenFramebuffer();
}

} /* flc */
} /* flw */
