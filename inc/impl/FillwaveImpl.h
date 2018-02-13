#pragma once

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

FLOGINIT("Engine", FERROR | FFATAL | FDEBUG | FINFO)

namespace flw {

/*! \struct Engine::EngineImpl
* \brief Private implementation of Fillwave GE.
*/

struct Engine::EngineImpl final {
#ifdef __ANDROID__
  EngineImpl(Engine* engine, std::string rootPath);
  EngineImpl(Engine* engine, ANativeActivity* activity);
#else

  EngineImpl(Engine *engine, GLint argc, GLchar *const argv[]);

#endif

  ~EngineImpl();

  Engine *mEngine;

  /* Asset loader */
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  Assimp::Importer mImporter;
#else

#endif

  /* Screen */
  GLuint mWindowWidth = 1920;
  GLuint mWindowHeight = 1200;
  GLfloat mWindowAspectRatio = 1200.0f / 1920.0f;

  /* Loaders */
  flf::FontLoader mFontLoader;
  flf::FileLoader mFileLoader;
  flf::ProgramLoader mProgramLoader;

  /* Picking */
  flc::Texture2DRenderable* mPickingRenderableTexture;
  pu<flc::PixelBuffer> mPickingPixelBuffer;

  /* Resources */
  flf::CacheShader mShaders;
  flf::CacheProgram mPrograms;
  flf::CacheSampler mSamplers;
  std::vector<ps<flf::Text>> mTextManager;
  std::vector<ps<Font>> mFontManager;
  flf::CacheBuffer mBuffers;
  pu<flf::LightSystem> mLights;
  pu<flf::TextureSystem> mTextures;
  std::vector<flc::PostProcessingPass> mPostProcessingPasses;
  flc::Program* mProgramTextureLookup;

  /* Fences and barriers */
  puFence mFence;

  /* OQ */
  flc::Program *mProgramOcclusionBox;
  flc::VertexBufferPosition *mVBOOcclusion;
  flc::VertexArray *mVAOOcclusion;

  /* Input handlers */
  flf::vec<flf::EventHandler> mHandlers;

  /* Extras */
  pu<flf::Debugger> mDebugger;
  GLuint mFrameCounter;
  GLfloat mTimeFactor;
  ps<flf::Text> mFPSText;
  //flf::FPSCallback mTextFPSCallback;

  /* Startup */
  GLfloat mStartupTime;
  flc::Texture* mStartupTexture;
  const GLfloat mStartupTimeLimit = 8.0f;
  pu<flc::PostProcessingPass> mPostProcessingPassStartup;

  /* Options */
  GLboolean mIsOQ; /* Occlusion query */

  /* Scene */
  pu<flf::Scene> mScene;
  glm::vec3 mBackgroundColor;

  /* Initiatization */
  void init();
  void initExtensions();
  void initContext();
  void initPickingBuffer();
  void initPipelines();
  void initUniforms();
  void initManagement();
  void initExtras();
  void initOcclusionTest();
  void initStartup();

  /* Events */
  void onEvent(const flf::Event& event) const;
  void onResizeScreen(GLuint width, GLuint height);

  void attachHandler(std::function<void(const flf::Event&)>&& handler, flf::eEventType type);
  void detachHandlers();

  /* Evaluation */
  void evaluateShadowMaps();
  void evaluateDebugger();
  void evaluateDynamicTextures(GLfloat timeExpiredInSeconds);
  void evaluateTime(GLfloat timeExpiredInSeconds);
  void evaluateStartupAnimation(GLfloat time);

  /* Draw types */
  void draw(GLfloat time);
  void drawFront();
  void drawOcclusionPass();

#ifdef FILLWAVE_GLES_3_0
#else
  void drawLines(GLfloat time);
  void drawPoints(GLfloat time);
#endif
  void drawTexture(flc::Texture *t, flc::Program *p);
  void drawTexture(flc::Texture *t);

  /* IRenderer */
  void drawClear();
  void drawHUD();
  void drawSceneStartup();
  void drawScene(GLfloat time);
  void drawSceneCore();

  /* Picking */
  glm::ivec4 pickingBufferGetColor(GLubyte* data, GLuint x, GLuint y);

  void pick(GLuint x, GLuint y);

  /* Capture */
  void captureFramebufferToFile(const std::string& name);

  /* Reload */
  void reload();
  void reloadPickingBuffer();
};

#ifdef __ANDROID__

Engine::EngineImpl::EngineImpl(Engine* engine, std::string rootPath)
  : mEngine(engine)
  , mFileLoader(rootPath)
  , mProgramLoader(engine)
  , mFrameCounter(0)
  , mTimeFactor(1.0)
  , mTextFPSCallback(nullptr)
  , mStartupTime(0.0f)
  , mIsOQ(GL_FALSE)
  , mBackgroundColor(0.1, 0.1, 0.1) {
}

Engine::EngineImpl::EngineImpl(Engine* engine, ANativeActivity* activity)
  : mEngine(engine)
  , mFileLoader(activity->internalDataPath)
  , mProgramLoader(engine)
  , mFrameCounter(0)
  , mTimeFactor(1.0)
  , mTextFPSCallback(nullptr)
  , mStartupTime(0.0f)
  , mIsOQ(GL_FALSE)
  , mBackgroundColor(0.1, 0.1, 0.1) {

  flf::androidSetActivity(activity);

  flf::androidExtractAll();

#else

Engine::EngineImpl::EngineImpl(Engine *engine, GLint, GLchar *const argv[])
    : mEngine(engine)
    , mFileLoader(getFilePathOnly(argv[0]))
    , mProgramLoader(engine)
    , mShaders()
    , mFrameCounter(0)
    , mTimeFactor(1.0)
    //, mTextFPSCallback(nullptr)
    , mStartupTime(0.0f)
    , mIsOQ(GL_TRUE)
    , mBackgroundColor(0.1, 0.1, 0.1) {
#endif
}

Engine::EngineImpl::~EngineImpl() {
  if (mScene) {
    mScene.reset();
  }
  mTextManager.clear();
  mFontManager.clear();
  mPostProcessingPasses.clear();
}

void Engine::EngineImpl::init() {

  initExtensions();
  initContext();
  initManagement();
  initPipelines();
  initUniforms();
  initPickingBuffer();
  initOcclusionTest();
  initExtras();

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
  initStartup(engine);
#endif
//   mFence = puFence(new flc::Fence());
}

#ifdef FILLWAVE_GLES_3_0

inline void Engine::EngineImpl::initExtensions() {
  glesInitExtensions();
}

#else /* FILLWAVE_GLES_3_0 */

inline void Engine::EngineImpl::initExtensions() {
#ifdef GLEW_OK
  GLenum GlewInitResult;
  glewExperimental = GL_TRUE;

  GlewInitResult = glewInit();
  if (GL_NO_ERROR != glGetError()) {
    fLogE("glewInit returned INVALID_ENUM ... It may happen");
  }

  if (GLEW_OK != GlewInitResult) {
    fLogE("GLEW init failed. Error: ", GlewInitResult);
    exit(EXIT_FAILURE);
  } else {
    fLogD("OpenGL Version: ", glGetString(GL_VERSION));
  }
  GLint maxPatchVertices = 0;
  glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxPatchVertices);
  fLogD("Max supported patches for tesselation: ", maxPatchVertices);
  // suppress error if tesselation is not supported
  glGetError();

#endif /* GLEW_OK */
}

#endif /* FILLWAVE_GLES_3_0 */

inline void Engine::EngineImpl::initManagement() {
  mTextures = std::make_unique<flf::TextureSystem>(mFileLoader.getRootPath());
  mLights = std::make_unique<flf::LightSystem>();
}

inline void Engine::EngineImpl::initPipelines() {
  /* OT */
  mProgramOcclusionBox = mProgramLoader.getProgram(flf::EProgram::occlusionOptimizedQuery);

  /* T */
  mProgramTextureLookup = mProgramLoader.getProgram(flf::EProgram::quad);
}

inline void Engine::EngineImpl::initUniforms() {
  mProgramTextureLookup->use();
  mProgramTextureLookup->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
  flc::Program::disusePrograms();
}

inline void Engine::EngineImpl::initOcclusionTest() {
  std::vector<flc::VertexPosition> vec = flf::BoxOcclusion().getVertices();
  mVAOOcclusion = new flc::VertexArray();
  mVBOOcclusion = mBuffers.mVerticesPosition.store(mVAOOcclusion, vec);
  mVBOOcclusion->initAttributes(mProgramOcclusionBox->getHandle());
  mVAOOcclusion->bind();
  mVBOOcclusion->bind();
  mVBOOcclusion->attributesSetForVAO();
  mVBOOcclusion->send();
  flc::VertexArray::unbindVAO();
}

inline void Engine::EngineImpl::initStartup() {

  flc::Program *program = mProgramLoader.getProgram(flf::EProgram::quadCustomFragmentShaderStartup);

  program->use();
  program->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
  program->uniformPush("uScreenFactor", mWindowAspectRatio);
  flc::Program::disusePrograms();

  mPostProcessingPassStartup = std::make_unique<flc::PostProcessingPass>(program,
                                                                     mTextures->getDynamic("fillwave_quad_startup.frag",
                                                                                           program,
                                                                                           glm::ivec2(mWindowWidth,
                                                                                                      mWindowHeight)),
                                                                     mStartupTimeLimit);

  fLogD("Post processing startup pass added");

  mStartupTexture = mTextures->get("logo.png", flf::ECompression::none);
  if (mStartupTexture) {
    return;
  }

  mStartupTexture = mTextures->get("textures/logo.png", flf::ECompression::none);
  if (mStartupTexture) {
    return;
  }

  mStartupTexture = mTextures->get("64_64_64.color", flf::ECompression::none);
  fLogE("Fillwave startup logo could not be executed");
}

inline void Engine::EngineImpl::initPickingBuffer() {
  mPickingPixelBuffer = std::make_unique<flc::PixelBuffer>(GL_STREAM_READ);
  reloadPickingBuffer();
}

inline void Engine::EngineImpl::initExtras() {
  /* Debugger */
  mDebugger = std::make_unique<flf::Debugger>(mEngine);

  /* Tesselation */
  glPatchParameteri(GL_PATCH_VERTICES, 3);
  /* Suppress error if setting patch up fails */
  glGetError();
}

void Engine::EngineImpl::reload() {

  initContext();

  for (auto &it : mShaders) {
    it.second->reload();
  }

  for (auto &it : mPrograms) {
    it.second->reload();
  }

  mTextures->reload();

  for (auto &it : mSamplers) {
    it.second->reload();
  }

  for (auto &it : mBuffers.mVertexArrays) {
    it.second->reload();
  }

  mPickingPixelBuffer->reload();
  reloadPickingBuffer();
}

inline void Engine::EngineImpl::reloadPickingBuffer() {
  mPickingRenderableTexture = mTextures->getColor2D(mWindowWidth, mWindowHeight);

  mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);
  mPickingPixelBuffer->bind();
  mPickingPixelBuffer->setLoaded(GL_FALSE);
  mPickingPixelBuffer->send();
  glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  fLogC("glReadPixels");
  mPickingPixelBuffer->unbind();
}

inline void Engine::EngineImpl::initContext(void) {
  glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  fLogC("Could not set OpenGL depth testing options");
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  fLogC("Could not set OpenGL culling options");
}

void Engine::EngineImpl::draw(GLfloat time) {
#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
  /* Draw startup animation */
  if (mStartupTime < mStartupTimeLimit) {
    evaluateStartupAnimation(time);
    mStartupTime += time;
    return;
  }
#endif

  if (mScene) {
    /* count this frame */
    mFrameCounter++;

    /* Clear main framebuffer */
    glClearDepth(1.0f);

    /* Calculate dynamic textures */
    mTextures->evaluateDynamicTextures(time);

    /* Lights evaluation */
    glDepthMask(GL_TRUE);
    evaluateShadowMaps();
    drawScene(time);
    drawFront();
  }
}

inline void Engine::EngineImpl::drawFront() {
  drawHUD();
  evaluateDebugger();
  mScene->drawCursor();
  mScene->updateDependencies();
  mScene->updateRenderer();
}

#ifdef FILLWAVE_GLES_3_0
#else

void Engine::EngineImpl::drawLines(GLfloat time) {

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
  /* Draw startup animation */
  if (mStartupTime < mStartupTimeLimit) {
    evaluateStartupAnimation(time);
    mStartupTime += time;
    return;
  }
#endif

  /* count this frame */
  mFrameCounter++;

  /* clear main framebuffer */
  glClearDepth(1.0f);

  /* Calculate dynamic textures */
  mTextures->evaluateDynamicTextures(time);

  /* Lights evaluation */
  if (mScene) {
    evaluateShadowMaps();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    drawScene(time);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawFront();
  }
}

void Engine::EngineImpl::drawPoints(GLfloat time) {

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
  /* Draw startup animation */
  if (mStartupTime < mStartupTimeLimit) {
    evaluateStartupAnimation(time);
    mStartupTime += time;
    return;
  }
#endif

  /* count this frame */
  mFrameCounter++;

  /* clear main framebuffer */
  glClearDepth(1.0f);

  /* Calculate dynamic textures */
  mTextures->evaluateDynamicTextures(time);

  /* Lights evaluation */
  if (mScene) {
    evaluateShadowMaps();
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    drawScene(time);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawFront();
  }
}

#endif

inline void Engine::EngineImpl::drawHUD() {
  if (mScene) {
    mScene->drawHUD();
  }
  for (auto &it : mTextManager) {
    it->draw();
  }
}

void Engine::EngineImpl::drawTexture(flc::Texture *t, flc::Program *p) {
  p->use();
  t->bind(FILLWAVE_DIFFUSE_UNIT);
  p->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  t->unbind();
  flc::Program::disusePrograms();
}

void Engine::EngineImpl::drawTexture(flc::Texture *t) {
  mProgramTextureLookup->use();
  mProgramTextureLookup->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
  t->bind(FILLWAVE_DIFFUSE_UNIT);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  t->unbind();
}

inline void Engine::EngineImpl::drawClear() {
  glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void Engine::EngineImpl::drawScene(GLfloat time) {

  evaluateTime(time);

  if (mPostProcessingPasses.size()) {
    auto _compare_function = [](flc::PostProcessingPass &pass) -> bool {
      return pass.isFinished();
    };
    auto _begin = mPostProcessingPasses.begin();
    auto _end = mPostProcessingPasses.end();

    flc::Texture2DRenderableDynamic* textureNext;
    flc::Texture2DRenderableDynamic* textureCurrent = (*_begin).getFrame();

    flc::Program* programCurrent;

    drawClear();
    textureCurrent->bindForWriting();
    drawSceneCore();

    for (auto it = _begin; it != _end; it++) {

      auto next = it + 1;

      if (next != _end) {

        textureNext = (*next).getFrame();
        textureCurrent = (*it).getFrame();
        programCurrent = (*it).getProgram();

        textureNext->bindForWriting();

        drawClear();

        textureCurrent->draw(0.0f);

        textureNext->draw(time);

        textureNext->bindForReading();

      } else {

        flc::Framebuffer::bindScreenFramebuffer();

        // render to current bound framebuffer using textureCurrent as a texture to post process
        textureCurrent->draw(time);

        textureCurrent = (*it).getFrame();
        programCurrent = (*it).getProgram();

        // render to current bound framebuffer using textureCurrent as a texture to post process
        drawTexture(textureCurrent, programCurrent);
      }

      (*it).checkTime(time);
    }

    auto it = remove_if(_begin, _end, _compare_function);

    mPostProcessingPasses.erase(it, _end);

  } else {
    drawSceneCore();
  }
}

inline void Engine::EngineImpl::drawSceneCore() {
  if (mIsOQ) {
    drawOcclusionPass();
  }
  drawClear();
  mScene->draw();
}

inline void Engine::EngineImpl::drawOcclusionPass() {
  mVAOOcclusion->bind();

  glDisable(GL_CULL_FACE);
  glDepthMask(GL_FALSE);
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

  mScene->drawOcclusion();

  glEnable(GL_CULL_FACE);
  glDepthMask(GL_TRUE);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

  flc::VertexArray::unbindVAO();
}

inline void Engine::EngineImpl::evaluateStartupAnimation(GLfloat time) {

  drawClear();

  flc::Texture2DRenderableDynamic *t = mPostProcessingPassStartup->getFrame();

  t->bindForWriting();

  drawTexture(mStartupTexture);

  flc::Framebuffer::bindScreenFramebuffer();

  t->draw(time);

  drawTexture(t, mPostProcessingPassStartup->getProgram());

  mPostProcessingPassStartup->checkTime(time);
}

inline void Engine::EngineImpl::evaluateShadowMaps() {

  glDepthMask(GL_TRUE);

  mLights->updateLightEntities();

  GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;

  flc::Texture2DRenderable *light2DTexture;
  for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
    light2DTexture = mLights->mLightsSpot[i]->getShadowTexture();
    light2DTexture->bindForWriting();
    light2DTexture->bind(currentTextureUnit++);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    mScene->drawDepth(*(mLights->mLightsSpot[i]->getShadowCamera()));
  }

  for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
    light2DTexture = mLights->mLightsDirectional[i]->getShadowTexture();
    light2DTexture->bindForWriting();
    light2DTexture->bind(currentTextureUnit++);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    mScene->drawDepth(*(mLights->mLightsDirectional[i]->getShadowCamera()));
  }

  for (size_t i = 0; i < mLights->mLightsPoint.size(); i++) {
    flf::LightPoint *lightPoint = mLights->mLightsPoint[i].get();
    flc::Texture3DRenderable *light3DTexture = lightPoint->getShadowTexture();
    glm::vec3 lightPosition(lightPoint->getTranslation());
    light3DTexture->bindForWriting();
    light3DTexture->bind(currentTextureUnit);
    for (GLint j = GL_TEXTURE_CUBE_MAP_POSITIVE_X; j <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; j++) {
      light3DTexture->setAttachmentFace(j, GL_COLOR_ATTACHMENT0);
      glClearColor(0.0, 0.0, 0.0, 1.0);
      glClear(GL_DEPTH_BUFFER_BIT);
      mScene->drawDepthColor(*(lightPoint->getShadowCamera(j)), lightPosition);
    }
    currentTextureUnit++;
  }
  flc::Framebuffer::bindScreenFramebuffer();
}

inline void Engine::EngineImpl::evaluateTime(GLfloat timeExpiredInSeconds) {
  if (mTimeFactor) {
    flf::EventData data;
    data.mTime = {
        timeExpiredInSeconds
    };
    ;

    mScene->onEvent(flf::Event(flf::eEventType::time, data));
    mScene->stepInTime(timeExpiredInSeconds);
  }
}

inline void Engine::EngineImpl::evaluateDebugger() {
  GLint mCurentTextureUnit = 0;
  GLint id = 0;
  switch (mDebugger->getState()) {
    case EDebuggerState::lightsSpot:
      mCurentTextureUnit = 0;
      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
        mDebugger->renderFromCamera(*(mLights->mLightsSpot[i]->getShadowCamera()), mCurentTextureUnit++);
      }
      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
        mDebugger->renderFromCamera(*(mLights->mLightsDirectional[i]->getShadowCamera()), mCurentTextureUnit++);
      }
      mCurentTextureUnit = 0;
      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
        mDebugger->renderDepthPerspective(mCurentTextureUnit++);
      }
      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
        mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
      }
      break;
    case EDebuggerState::lightsSpotDepth:
      mCurentTextureUnit = 0;
      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
        mDebugger->renderDepthPerspective(mCurentTextureUnit++);
      }
      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
        mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
      }
      break;
    case EDebuggerState::lightsSpotColor:
      mCurentTextureUnit = 0;
      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
        mDebugger->renderFromCamera(*(mLights->mLightsSpot[i]->getShadowCamera()), mCurentTextureUnit++);
      }
      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
        mDebugger->renderFromCamera(*(mLights->mLightsDirectional[i]->getShadowCamera()), mCurentTextureUnit++);
      }
      break;
    case EDebuggerState::lightsPoint:
      break;
    case EDebuggerState::lightsPointDepth: // only light 0
      break;
    case EDebuggerState::lightsPointColor:
      for (size_t j = 0; j < mLights->mLightsPoint.size(); j++) {
        for (int i = GL_TEXTURE_CUBE_MAP_POSITIVE_X; i <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; i++) {
          flf::CameraPerspective cameraPF = *(mLights->mLightsPoint[j]->getShadowCamera(i));
          mDebugger->renderFromCamera(cameraPF, id++);
        }
      }
      break;
    case EDebuggerState::pickingMap:
      mDebugger->renderPickingMap();
      break;
    case EDebuggerState::off:
    case EDebuggerState::toggleState:
      break;
  }
}

void Engine::EngineImpl::onResizeScreen(GLuint width, GLuint height) {

  mWindowWidth = width;
  mWindowHeight = height;
  mWindowAspectRatio = static_cast<GLfloat>(mWindowHeight) / static_cast<GLfloat>
  (mWindowWidth);

  glViewport(0, 0, mWindowWidth, mWindowHeight);

  mTextures->resize(mWindowWidth, mWindowHeight);
  mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);
}

void Engine::EngineImpl::onEvent(const flf::Event& event) const {
  for (const auto& handler : mHandlers) {
    handler.handle(event);
  }
  mScene->onEvent(event);
}

void Engine::EngineImpl::attachHandler(std::function<void(const flf::Event&)>&& handler, flf::eEventType type) {
  mHandlers.emplace_back(type, std::move(handler));
}

void Engine::EngineImpl::detachHandlers() {
  mHandlers.clear();
}

glm::ivec4 Engine::EngineImpl::pickingBufferGetColor(GLubyte *data, GLuint x, GLuint y) {
  y = mWindowHeight - y;
  GLuint id = 0;
  GLuint r = 0;
  GLuint g = 0;
  GLuint b = 0;
  GLuint a = 0;

  if (x < mWindowWidth && y < mWindowHeight) {
    id = (x + y * mWindowWidth) * 4;
    b = data[id];
    g = data[id + 1];
    r = data[id + 2];
    a = data[id + 3];
  }
  return glm::ivec4(r, g, b, a);
}

void Engine::EngineImpl::pick(GLuint x, GLuint y) {
  mPickingRenderableTexture->bindForRendering();
  drawClear();
  mScene->drawPicking();
  mPickingPixelBuffer->bind();
  glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  fLogC("glReadPixels failed");
#ifdef FILLWAVE_GLES_3_0
  GLubyte* data = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
  GLubyte *data = (GLubyte *) mPickingPixelBuffer->map(GL_READ_WRITE);
#endif

  glm::ivec4 colorRead = pickingBufferGetColor(data, x, y);
  mPickingPixelBuffer->unmap();
  mPickingPixelBuffer->unbind();
  flc::Framebuffer::bindScreenFramebuffer();
  mScene->draw();
  mScene->pick(colorRead);
}

void Engine::EngineImpl::captureFramebufferToFile(const std::string &name) {
  mPickingRenderableTexture->bindForRendering();
  drawClear();
  mScene->draw();
  mPickingPixelBuffer->bind();
  glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  fLogC("reading pixel buffer failed");
#ifdef FILLWAVE_GLES_3_0
  GLubyte* data = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
  GLubyte *data = (GLubyte *) mPickingPixelBuffer->map(GL_READ_WRITE);
#endif
  data[mWindowWidth * mWindowHeight * 4] = '\0';
  FILE *file;
  auto errorNo = fopen_s(&file, mFileLoader.getRootPath(name).c_str(), "w");
  if (errorNo) {
    fLogE("Error when takin' screenshot");
    exit(1);
  }
  for (GLuint i = 0; i < mWindowWidth * mWindowHeight; i++) {
    fprintf(file, "%c", data[4 * i]);
    fprintf(file, "%c", data[4 * i + 1]);
    fprintf(file, "%c", data[4 * i + 2]);
    fprintf(file, "%c", data[4 * i] + 3);
  }
  fclose(file);
  mPickingPixelBuffer->unmap();
  mPickingPixelBuffer->unbind();
  flc::Framebuffer::bindScreenFramebuffer();
  mScene->draw();
}
} /* flw */

#undef FILLWAVE_FOPEN
