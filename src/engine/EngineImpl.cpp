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

#include "fillwave/Core.h"
#include "fillwave/Debugger.h"
#include "fillwave/Framework.h"
#include "fillwave/Framework.h"

/* Management */
#include "fillwave/management/CacheProgram.h"
#include "fillwave/management/Cachehader.h"
#include "fillwave/management/CacheSampler.h"
#include "fillwave/management/LightSystem.h"
#include "fillwave/management/TextureSystem.h"

#include "fillwave/actions/EventHandler.h"
#include "fillwave/common/Macros.h"

#ifdef __ANDROID__
struct ANativeActivity;
#else /* __ANDROID__ */
#include "fillwave/common/Strings.h"
#endif /* __ANDROID__ */

#include "fillwave/loaders/FileLoader.h"
#include "fillwave/management/CacheBuffer.h"

namespace flw {


//Engine::EngineImpl(Engine* engine, std::string rootPath)
//  : mEngine(engine)
//  , mFileLoader(rootPath)
//  , mProgramLoader(engine)
//  , mFrameCounter(0)
//  , mTimeFactor(1.0)
//  , mTextFPSCallback(nullptr)
//  , mStartupTime(0.0f)
//  , mIsOQ(GL_FALSE)
//  , mBackgroundColor(0.1, 0.1, 0.1) {
//}
//
//Engine::EngineImpl(Engine* engine, ANativeActivity* activity)
//  : mEngine(engine)
//  , mFileLoader(activity->internalDataPath)
//  , mProgramLoader(engine)
//  , mFrameCounter(0)
//  , mTimeFactor(1.0)
//  , mTextFPSCallback(nullptr)
//  , mStartupTime(0.0f)
//  , mIsOQ(GL_FALSE)
//  , mBackgroundColor(0.1, 0.1, 0.1) {
//
//  flf::androidSetActivity(activity);
//
//  flf::androidExtractAll();

//#else

//Engine::EngineImpl(Engine *engine, GLint, GLchar *const argv[])
//  : mEngine(engine)
//  , mFileLoader(getFilePathOnly(argv[0]))
//  , mProgramLoader(engine)
//  , mShaders()
//  , mFrameCounter(0)
//  , mTimeFactor(1.0)
//  //, mTextFPSCallback(nullptr)
//  , mStartupTime(0.0f)
//  , mIsOQ(GL_TRUE)
//  , mBackgroundColor(0.1, 0.1, 0.1) {
//#endif
//}

//Engine::~EngineImpl() {
//  if (mScene) {
//    mScene.reset();
//  }
//  mTextManager.clear();
//  mFontManager.clear();
//  mPostProcessingPasses.clear();
//}

//void Engine::init() {
//
//  initExtensions();
//  initContext();
//  initManagement();
//  initPipelines();
//  initUniforms();
//  initPickingBuffer();
//  initOcclusionTest();
//  initExtras();
//
//#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
//  initStartup(engine);
//#endif
////   mFence = puFence(new flc::Fence());
//}

#ifdef FILLWAVE_GLES_3_0

void Engine::initExtensions() {
  glesInitExtensions();
}

#else /* FILLWAVE_GLES_3_0 */



#endif /* FILLWAVE_GLES_3_0 */

//void Engine::initManagement() {
//  mTextures = std::make_unique<flf::TextureSystem>(mFileLoader.getRootPath());
//  mLights = std::make_unique<flf::LightSystem>();
//}

//void Engine::initPipelines() {
//  /* OT */
//  mProgramOcclusionBox = mProgramLoader.getProgram(flf::EProgram::occlusionOptimizedQuery);
//
//  /* T */
//  mProgramTextureLookup = mProgramLoader.getProgram(flf::EProgram::quad);
//}

//void Engine::initUniforms() {
//  mProgramTextureLookup->use();
//  mProgramTextureLookup->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
//  flc::Program::disusePrograms();
//}

//void Engine::initOcclusionTest() {
//  flf::vec<flc::VertexPosition> vec = flf::BoxOcclusion().getVertices();
//  mVAOOcclusion = new flc::VertexArray();
//  mVBOOcclusion = mBuffers.mVerticesPosition.store(mVAOOcclusion, vec);
//  mVBOOcclusion->initAttributes(mProgramOcclusionBox->getHandle());
//  mVAOOcclusion->bind();
//  mVBOOcclusion->bind();
//  mVBOOcclusion->attributesSetForVAO();
//  mVBOOcclusion->send();
//  flc::VertexArray::unbindVAO();
//}
//
//void Engine::initStartup() {
//
//  auto program = mProgramLoader.getProgram(flf::EProgram::quadCustomFragmentShaderStartup);
//
//  program->use();
//  program->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
//  program->uniformPush("uScreenFactor", mWindowAspectRatio);
//  flc::Program::disusePrograms();
//
//  mPostProcessingPassStartup = std::make_unique<flc::PostProcessingPass>(program,
//                                                                         mTextures->getDynamic("fillwave_quad_startup.frag",
//                                                                                               program,
//                                                                                               glm::ivec2(mWindowWidth,
//                                                                                                          mWindowHeight)),
//                                                                         mStartupTimeLimit);
//
//  fLogD("Post processing startup pass added");
//
//  mStartupTexture = mTextures->get("logo.png", flf::ECompression::none);
//  if (mStartupTexture) {
//    return;
//  }
//
//  mStartupTexture = mTextures->get("textures/logo.png", flf::ECompression::none);
//  if (mStartupTexture) {
//    return;
//  }
//
//  mStartupTexture = mTextures->get("64_64_64.color", flf::ECompression::none);
//  fLogE("Fillwave startup logo could not be executed");
//}
//
//void Engine::initPickingBuffer() {
//  mPickingPixelBuffer = std::make_unique<flc::PixelBuffer>(GL_STREAM_READ);
//  reloadPickingBuffer();
//}
//
//void Engine::initExtras() {
//  /* Debugger */
//  mDebugger = std::make_unique<flf::Debugger>(mEngine);
//
//#ifdef FILLWAVE_COMPILATION_PC_GLES
//#else
//  /* Tesselation */
//  glPatchParameteri(GL_PATCH_VERTICES, 3);
//#endif // FILLWAVE_COMPILATION_PC_GLES
//
//  /* Suppress error if setting patch up fails */
//  glGetError();
//}

//void Engine::reload() {
//
//  initContext();
//
//  for (auto &it : mShaders) {
//    it.second->reload();
//  }
//
//  for (auto &it : mPrograms) {
//    it.second->reload();
//  }
//
//  mTextures->reload();
//
//  for (auto &it : mSamplers) {
//    it.second->reload();
//  }
//
//  for (auto &it : mBuffers.mVertexArrays) {
//    it.second->reload();
//  }
//
//  mPickingPixelBuffer->reload();
//  reloadPickingBuffer();
//}
//
//void Engine::reloadPickingBuffer() {
//  mPickingRenderableTexture = mTextures->getColor2D(mWindowWidth, mWindowHeight);
//
//  mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);
//  mPickingPixelBuffer->bind();
//  mPickingPixelBuffer->setLoaded(GL_FALSE);
//  mPickingPixelBuffer->send();
//  glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//  fLogC("glReadPixels");
//  mPickingPixelBuffer->unbind();
//}

//void Engine::initContext(void) {
//  glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f);
//  glEnable(GL_DEPTH_TEST);
//  glDepthFunc(GL_LEQUAL);
//  fLogC("Could not set OpenGL depth testing options");
//  glEnable(GL_CULL_FACE);
//  glCullFace(GL_BACK);
//  glFrontFace(GL_CCW);
//  fLogC("Could not set OpenGL culling options");
//}

//void Engine::draw(GLfloat time) {
//#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
//  /* Draw startup animation */
//  if (mStartupTime < mStartupTimeLimit) {
//    evaluateStartupAnimation(time);
//    mStartupTime += time;
//    return;
//  }
//#endif
//
//  if (mScene) {
//    /* count this frame */
//    mFrameCounter++;
//
//    /* Clear main framebuffer */
//    glClearDepth(1.0f);
//
//    /* Calculate dynamic textures */
//    mTextures->evaluateDynamicTextures(time);
//
//    /* Lights evaluation */
//    glDepthMask(GL_TRUE);
//    evaluateShadowMaps();
//    drawScene(time);
//    drawFront();
//  }
//}
//
//void Engine::drawFront() {
//  drawHUD();
//  evaluateDebugger();
//  mScene->drawCursor();
//  mScene->updateDependencies();
//  mScene->updateRenderer();
//}
//
//#ifdef FILLWAVE_GLES_3_0
//#else
//
//void Engine::drawLines(GLfloat time) {
//
//#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
//  /* Draw startup animation */
//  if (mStartupTime < mStartupTimeLimit) {
//    evaluateStartupAnimation(time);
//    mStartupTime += time;
//    return;
//  }
//#endif
//
//  /* count this frame */
//  mFrameCounter++;
//
//  /* clear main framebuffer */
//  glClearDepth(1.0f);
//
//  /* Calculate dynamic textures */
//  mTextures->evaluateDynamicTextures(time);
//
//  /* Lights evaluation */
//  if (mScene) {
//    evaluateShadowMaps();
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    drawScene(time);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    drawFront();
//  }
//}
//
//void Engine::drawPoints(GLfloat time) {
//
//#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
//  /* Draw startup animation */
//  if (mStartupTime < mStartupTimeLimit) {
//    evaluateStartupAnimation(time);
//    mStartupTime += time;
//    return;
//  }
//#endif
//
//  /* count this frame */
//  mFrameCounter++;
//
//  /* clear main framebuffer */
//  glClearDepth(1.0f);
//
//  /* Calculate dynamic textures */
//  mTextures->evaluateDynamicTextures(time);
//
//  /* Lights evaluation */
//  if (mScene) {
//    evaluateShadowMaps();
//    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
//    drawScene(time);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    drawFront();
//  }
//}
//
//#endif
//
//void Engine::drawHUD() {
//  if (mScene) {
//    mScene->drawHUD();
//  }
//  for (auto &it : mTextManager) {
//    it->draw();
//  }
//}
//
//void Engine::drawTexture(flc::Texture *t, flc::Program *p) {
//  p->use();
//  t->bind(FILLWAVE_DIFFUSE_UNIT);
//  p->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
//  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//  t->unbind();
//  flc::Program::disusePrograms();
//}
//
//void Engine::drawTexture(flc::Texture *t) {
//  mProgramTextureLookup->use();
//  mProgramTextureLookup->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
//  t->bind(FILLWAVE_DIFFUSE_UNIT);
//  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//  t->unbind();
//}
//
//void Engine::drawClear() {
//  glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f);
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void Engine::drawScene(GLfloat time) {
//
//  evaluateTime(time);
//
//  if (mPostProcessingPasses.size()) {
//    auto _compare_function = [](flc::PostProcessingPass &pass) -> bool {
//      return pass.isFinished();
//    };
//    auto _begin = mPostProcessingPasses.begin();
//    auto _end = mPostProcessingPasses.end();
//
//    flc::Texture2DRenderableDynamic* textureNext;
//    flc::Texture2DRenderableDynamic* textureCurrent = (*_begin).getFrame();
//
//    flc::Program* programCurrent;
//
//    drawClear();
//    textureCurrent->bindForWriting();
//    drawSceneCore();
//
//    for (auto it = _begin; it != _end; it++) {
//
//      auto next = it + 1;
//
//      if (next != _end) {
//
//        textureNext = (*next).getFrame();
//        textureCurrent = (*it).getFrame();
//        programCurrent = (*it).getProgram();
//
//        textureNext->bindForWriting();
//
//        drawClear();
//
//        textureCurrent->draw(0.0f);
//
//        textureNext->draw(time);
//
//        textureNext->bindForReading();
//
//      } else {
//
//        flc::Framebuffer::bindScreenFramebuffer();
//
//        // render to current bound framebuffer using textureCurrent as a texture to post process
//        textureCurrent->draw(time);
//
//        textureCurrent = (*it).getFrame();
//        programCurrent = (*it).getProgram();
//
//        // render to current bound framebuffer using textureCurrent as a texture to post process
//        drawTexture(textureCurrent, programCurrent);
//      }
//
//      (*it).checkTime(time);
//    }
//
//    auto it = remove_if(_begin, _end, _compare_function);
//
//    mPostProcessingPasses.erase(it, _end);
//
//  } else {
//    drawSceneCore();
//  }
//}
//
//void Engine::drawSceneCore() {
//  if (mIsOQ) {
//    drawOcclusionPass();
//  }
//  drawClear();
//  mScene->draw();
//}
//
//void Engine::drawOcclusionPass() {
//  mVAOOcclusion->bind();
//
//  glDisable(GL_CULL_FACE);
//  glDepthMask(GL_FALSE);
//  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//
//  mScene->drawOcclusion();
//
//  glEnable(GL_CULL_FACE);
//  glDepthMask(GL_TRUE);
//  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//
//  flc::VertexArray::unbindVAO();
//}
//
//void Engine::evaluateStartupAnimation(GLfloat time) {
//
//  drawClear();
//
//  flc::Texture2DRenderableDynamic *t = mPostProcessingPassStartup->getFrame();
//
//  t->bindForWriting();
//
//  drawTexture(mStartupTexture);
//
//  flc::Framebuffer::bindScreenFramebuffer();
//
//  t->draw(time);
//
//  drawTexture(t, mPostProcessingPassStartup->getProgram());
//
//  mPostProcessingPassStartup->checkTime(time);
//}
//
//void Engine::evaluateShadowMaps() {
//
//  glDepthMask(GL_TRUE);
//
//  mLights->updateLightEntities();
//
//  GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;
//
//  flc::Texture2DRenderable *light2DTexture;
//  for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
//    light2DTexture = mLights->mLightsSpot[i]->getShadowTexture();
//    light2DTexture->bindForWriting();
//    light2DTexture->bind(currentTextureUnit++);
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glClear(GL_DEPTH_BUFFER_BIT);
//    mScene->drawDepth(*(mLights->mLightsSpot[i]->getShadowCamera()));
//  }
//
//  for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
//    light2DTexture = mLights->mLightsDirectional[i]->getShadowTexture();
//    light2DTexture->bindForWriting();
//    light2DTexture->bind(currentTextureUnit++);
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glClear(GL_DEPTH_BUFFER_BIT);
//    mScene->drawDepth(*(mLights->mLightsDirectional[i]->getShadowCamera()));
//  }
//
//  for (size_t i = 0; i < mLights->mLightsPoint.size(); i++) {
//    flf::LightPoint *lightPoint = mLights->mLightsPoint[i].get();
//    flc::Texture3DRenderable *light3DTexture = lightPoint->getShadowTexture();
//    glm::vec3 lightPosition(lightPoint->getTranslation());
//    light3DTexture->bindForWriting();
//    light3DTexture->bind(currentTextureUnit);
//    for (GLint j = GL_TEXTURE_CUBE_MAP_POSITIVE_X; j <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; j++) {
//      light3DTexture->setAttachmentFace(j, GL_COLOR_ATTACHMENT0);
//      glClearColor(0.0, 0.0, 0.0, 1.0);
//      glClear(GL_DEPTH_BUFFER_BIT);
//      mScene->drawDepthColor(*(lightPoint->getShadowCamera(j)), lightPosition);
//    }
//    currentTextureUnit++;
//  }
//  flc::Framebuffer::bindScreenFramebuffer();
//}
//
//void Engine::evaluateTime(GLfloat timeExpiredInSeconds) {
//  if (mTimeFactor) {
//    flf::EventData data;
//    data.mTime = {
//      timeExpiredInSeconds
//    };
//    ;
//
//    mScene->onEvent(flf::Event(flf::EEventType::time, data));
//    mScene->stepInTime(timeExpiredInSeconds);
//  }
//}
//
//void Engine::evaluateDebugger() {
//  GLint mCurentTextureUnit = 0;
//  GLint id = 0;
//  switch (mDebugger->getState()) {
//    case EDebuggerState::lightsSpot:
//      mCurentTextureUnit = 0;
//      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
//        mDebugger->renderFromCamera(*(mLights->mLightsSpot[i]->getShadowCamera()), mCurentTextureUnit++);
//      }
//      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
//        mDebugger->renderFromCamera(*(mLights->mLightsDirectional[i]->getShadowCamera()), mCurentTextureUnit++);
//      }
//      mCurentTextureUnit = 0;
//      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
//        mDebugger->renderDepthPerspective(mCurentTextureUnit++);
//      }
//      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
//        mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
//      }
//      break;
//    case EDebuggerState::lightsSpotDepth:
//      mCurentTextureUnit = 0;
//      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
//        mDebugger->renderDepthPerspective(mCurentTextureUnit++);
//      }
//      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
//        mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
//      }
//      break;
//    case EDebuggerState::lightsSpotColor:
//      mCurentTextureUnit = 0;
//      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
//        mDebugger->renderFromCamera(*(mLights->mLightsSpot[i]->getShadowCamera()), mCurentTextureUnit++);
//      }
//      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
//        mDebugger->renderFromCamera(*(mLights->mLightsDirectional[i]->getShadowCamera()), mCurentTextureUnit++);
//      }
//      break;
//    case EDebuggerState::lightsPoint:
//      break;
//    case EDebuggerState::lightsPointDepth: // only light 0
//      break;
//    case EDebuggerState::lightsPointColor:
//      for (size_t j = 0; j < mLights->mLightsPoint.size(); j++) {
//        for (int i = GL_TEXTURE_CUBE_MAP_POSITIVE_X; i <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; i++) {
//          flf::CameraPerspective cameraPF = *(mLights->mLightsPoint[j]->getShadowCamera(i));
//          mDebugger->renderFromCamera(cameraPF, id++);
//        }
//      }
//      break;
//    case EDebuggerState::pickingMap:
//      mDebugger->renderPickingMap();
//      break;
//    case EDebuggerState::off:
//    case EDebuggerState::toggleState:
//      break;
//  }
//}
//
//void Engine::onResizeScreen(GLuint width, GLuint height) {
//
//  mWindowWidth = width;
//  mWindowHeight = height;
//  mWindowAspectRatio = static_cast<GLfloat>(mWindowHeight) / static_cast<GLfloat>
//  (mWindowWidth);
//
//  glViewport(0, 0, mWindowWidth, mWindowHeight);
//
//  mTextures->resize(mWindowWidth, mWindowHeight);
//  mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);
//}
//
//void Engine::onEvent(const flf::Event& event) const {
//  for (const auto& handler : mHandlers) {
//    handler.handle(event);
//  }
//  mScene->onEvent(event);
//}
//
//void Engine::attachHandler(std::function<void(const flf::Event&)>&& handler, flf::EEventType type) {
//  mHandlers.emplace_back(type, std::move(handler));
//}
//
//void Engine::detachHandlers() {
//  mHandlers.clear();
//}
//
//glm::ivec4 Engine::pickingBufferGetColor(GLubyte *data, GLuint x, GLuint y) {
//  y = mWindowHeight - y;
//  GLuint id = 0;
//  GLuint r = 0;
//  GLuint g = 0;
//  GLuint b = 0;
//  GLuint a = 0;
//
//  if (x < mWindowWidth && y < mWindowHeight) {
//    id = (x + y * mWindowWidth) * 4;
//    b = data[id];
//    g = data[id + 1];
//    r = data[id + 2];
//    a = data[id + 3];
//  }
//  return glm::ivec4(r, g, b, a);
//}
//
//void Engine::pick(GLuint x, GLuint y) {
//  mPickingRenderableTexture->bindForRendering();
//  drawClear();
//  mScene->drawPicking();
//  mPickingPixelBuffer->bind();
//  glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//  fLogC("glReadPixels failed");
//#ifdef FILLWAVE_GLES_3_0
//  GLubyte* data = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
//#else
//  GLubyte *data = (GLubyte *) mPickingPixelBuffer->map(GL_READ_WRITE);
//#endif
//
//  glm::ivec4 colorRead = pickingBufferGetColor(data, x, y);
//  mPickingPixelBuffer->unmap();
//  mPickingPixelBuffer->unbind();
//  flc::Framebuffer::bindScreenFramebuffer();
//  mScene->draw();
//  mScene->pick(colorRead);
//}
//
//void Engine::captureFramebufferToFile(const std::string &name) {
//  mPickingRenderableTexture->bindForRendering();
//  drawClear();
//  mScene->draw();
//  mPickingPixelBuffer->bind();
//  glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//  fLogC("reading pixel buffer failed");
//#ifdef FILLWAVE_GLES_3_0
//  GLubyte* data = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
//#else
//  GLubyte *data = (GLubyte *) mPickingPixelBuffer->map(GL_READ_WRITE);
//#endif
//  data[mWindowWidth * mWindowHeight * 4] = '\0';
//  FILE *file;
//  auto errorNo = fopen_s(&file, mFileLoader.getRootPath(name).c_str(), "w");
//  if (errorNo) {
//    fLogE("Error when takin' screenshot");
//    exit(1);
//  }
//  for (GLuint i = 0; i < mWindowWidth * mWindowHeight; i++) {
//    fprintf(file, "%c", data[4 * i]);
//    fprintf(file, "%c", data[4 * i + 1]);
//    fprintf(file, "%c", data[4 * i + 2]);
//    fprintf(file, "%c", data[4 * i] + 3);
//  }
//  fclose(file);
//  mPickingPixelBuffer->unmap();
//  mPickingPixelBuffer->unbind();
//  flc::Framebuffer::bindScreenFramebuffer();
//  mScene->draw();
//}
} /* flw */

#undef FILLWAVE_FOPEN
