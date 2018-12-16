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

#include <flw/flf/management/LightSystem.h>

#include <flw/flf/loaders/ProgramLoader.h>

#include <flw/flc/extended/rendering/FramebufferGeometry.h>

#include <flw/Fillwave.h>

namespace flw {
namespace flf {

Debugger::Debugger(Engine *engine, GLuint howManyDebugWindows)
  : IReloadable(engine)
  , mState(EDebuggerState::off)
  , mEngine(engine)
  , mVBO(mEngine->storeBuffer<flc::VertexBufferDebug>(mVAO, 1.0f))
  , mMiniwindowsOccupied(0) {

  mDebugWindows.reserve(howManyDebugWindows);
  const glm::vec2 size = mEngine->getScreenSize();
  const float sizeFactor = 1.0f / static_cast<float>(howManyDebugWindows);
  const float offsetY = 1.0f - sizeFactor * (size.x/size.y);
  for (GLuint i = 0; i < howManyDebugWindows; ++i) {
    const float offsetX = static_cast<float>(i) * sizeFactor;
    DebugWindowInfo window = {
      { size.x * sizeFactor , size.y * sizeFactor }
      , { size.x * offsetX , size.y * offsetY }
    };
    mDebugWindows.push_back(window);
  }

  ProgramLoader loader(engine);

  mProgram = loader.getProgram(EProgram::debugger);

  initPipeline();
  initVBO();
  initVAO();
  initUniformsCache();
}

Debugger::~Debugger() = default;

void Debugger::setState(EDebuggerState state) {
  if (state != EDebuggerState::toggleState) {
    mState = state;
    return;
  }
  switch (mState) {
    case EDebuggerState::lightsSpot:
      mState = EDebuggerState::lightsSpotDepth;
      break;
    case EDebuggerState::lightsSpotDepth:
      mState = EDebuggerState::lightsSpotColor;
      break;
    case EDebuggerState::lightsSpotColor:
      mState = EDebuggerState::lightsPoint;
      break;
    case EDebuggerState::lightsPoint:
      mState = EDebuggerState::lightsPointDepth;
      break;
    case EDebuggerState::lightsPointDepth:
      mState = EDebuggerState::lightsPointColor;
      break;
    case EDebuggerState::lightsPointColor:
      mState = EDebuggerState::pickingMap;
      break;
    case EDebuggerState::pickingMap:
      mState = EDebuggerState::off;
      break;
    case EDebuggerState::off:
      mState = EDebuggerState::lightsSpot;
      break;
    case EDebuggerState::toggleState:
      break;
  }
}

EDebuggerState Debugger::getState() {
  return mState;
}

void Debugger::prepareDebugWindow(GLint id) {
  DebugWindowInfo& win = mDebugWindows[id];
  glViewport(win.offset.x, win.offset.y, win.size.x, win.size.y);
  glClear(GL_DEPTH_BUFFER_BIT);
}

void Debugger::renderFromCamera(ICamera &c, GLint id) {
  prepareDebugWindow(id);
  mEngine->getCurrentScene()->draw(c);
  glViewport(0, 0, mEngine->getScreenSize()[0], mEngine->getScreenSize()[1]);
}

void Debugger::renderPickingMap() {
  prepareDebugWindow(mDebugWindows.size() - 1);
  mEngine->getCurrentScene()->drawPicking();
  glViewport(0, 0, mEngine->getScreenSize()[0], mEngine->getScreenSize()[1]);
}

void Debugger::renderDepthOrthographic(GLint id) {
  prepareDebugWindow(id);

  mProgram->use();

  mVAO->bind();

  auto light = mEngine->getLightSystem().mLightsDirectional[id].get();

  auto cam = light->getShadowCamera();

  light->getShadowTexture()->mTexture2D.bind(FILLWAVE_SHADOW_FIRST_UNIT + id, 0);

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  flc::Uniform::push(mULCTextureUnit, id);
  flc::Uniform::push(mULCNearPlane, cam->getProjectionNearPlane());
  flc::Uniform::push(mULCFarPlane, cam->getProjectionFarPlane());

  glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  flc::Texture2D::unbind2DTextures();
  flc::VertexArray::unbindVAO();
  flc::Program::disusePrograms();

  glViewport(0, 0, mEngine->getScreenSize()[0], mEngine->getScreenSize()[1]);
}

void Debugger::renderDepthPerspective(GLint id) {
  prepareDebugWindow(id);

  glClear(GL_DEPTH_BUFFER_BIT);

  mProgram->use();

  mVAO->bind();

  auto light = mEngine->getLightSystem().mLightsSpot[id].get();

  auto cam = *(light->getShadowCamera());

  light->getShadowTexture()->mTexture2D.bind(FILLWAVE_SHADOW_FIRST_UNIT + id);

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  flc::Uniform::push(mULCTextureUnit, FILLWAVE_SHADOW_FIRST_UNIT + id);
  flc::Uniform::push(mULCNearPlane, cam.getProjectionNearPlane());
  flc::Uniform::push(mULCFarPlane, cam.getProjectionFarPlane());

  glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  flc::Texture2D::unbind2DTextures();
  flc::VertexArray::unbindVAO();
  flc::Program::disusePrograms();

  glViewport(0, 0, mEngine->getScreenSize()[0], mEngine->getScreenSize()[1]);
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
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20) || defined(FILLWAVE_BACKEND_OPENGL_ES_30)
#else
  mSampler->bind();
#endif
  mVAO->bind();

  mVBO->bind();
  mVBO->setLoaded(GL_FALSE);
  mVBO->send();
  mVBO->attributesSetForVAO();

  flc::VertexArray::unbindVAO();
}

inline void Debugger::initVBO() {
  mVBO->initAttributes(mProgram->getHandle());
}

} /* flf */
} /* flw */

