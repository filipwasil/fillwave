/*
 * Debugger.cpp
 *
 *  Created on: Jul 26, 2014
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


#include <fillwave/core/buffers/VertexBufferDebug.h>
#include <fillwave/Fillwave.h>

#include <fillwave/core/rendering/FramebufferGeometry.h>

#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/management/LightSystem.h>


namespace flw {
namespace flf {

Debugger::Debugger(Engine *engine, GLsizei howManyDebugWindows)
  : IReloadable(engine), mState(eDebuggerState::eOff), mEngine(engine)
  , mVBO(mEngine->storeBuffer<flc::VertexBufferDebug>(mVAO, 1.0f))
  , mMiniwindowsOccupied(0) {

  mDebugWindows.reserve(howManyDebugWindows);
  const float sizeFactor = 1.0f / static_cast<float>(howManyDebugWindows);
  const float offsetY = 1.0f - sizeFactor;
  for (int i = 0; i < howManyDebugWindows; ++i)
  {
    const float offsetX = static_cast<float>(i) / static_cast<float>(howManyDebugWindows);
    DebugWindowInfo window = {
      {
        mEngine->getScreenSize()[0] * sizeFactor,
        mEngine->getScreenSize()[1] * sizeFactor
      },
      {
        mEngine->getScreenSize()[0] * offsetX,
        mEngine->getScreenSize()[1] * offsetY
      }
    };
    mDebugWindows.push_back(window);
  }

  ProgramLoader loader(engine);

  mProgram = loader.getDebugger();

  initPipeline();
  initVBO();
  initVAO();
  initUniformsCache();
}

void Debugger::setState(eDebuggerState state) {
  if (state == eDebuggerState::eToggleState) {
    switch (mState) {
      case eDebuggerState::eLightsSpot:
        mState = eDebuggerState::eLightsSpotDepth;
        break;
      case eDebuggerState::eLightsSpotDepth:
        mState = eDebuggerState::eLightsSpotColor;
        break;
      case eDebuggerState::eLightsSpotColor:
        mState = eDebuggerState::eLightsPoint;
        break;
      case eDebuggerState::eLightsPoint:
        mState = eDebuggerState::eLightsPointDepth;
        break;
      case eDebuggerState::eLightsPointDepth:
        mState = eDebuggerState::eLightsPointColor;
        break;
      case eDebuggerState::eLightsPointColor:
        mState = eDebuggerState::ePickingMap;
        break;
      case eDebuggerState::ePickingMap:
        mState = eDebuggerState::eOff;
        break;
      case eDebuggerState::eOff:
        mState = eDebuggerState::eLightsSpot;
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

void Debugger::prepareDebugWindow(GLint id)
{
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

void Debugger::renderDepthOrthographic(GLint id) { //xxx ujednolicić to całe lightID żeby można było usuwać światła
  prepareDebugWindow(id);

  mProgram->use();

  mVAO->bind();

  LightDirectional *light = mEngine->getLightSystem()->mLightsDirectional[id].get();

  ICamera *cam = light->getShadowCamera();

  light->getShadowTexture()->bind(GLint(FILLWAVE_SHADOW_FIRST_UNIT + id));

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

void Debugger::renderDepthPerspective(GLint id) { //xxx ujednolicić to całe lightID żeby można było usuwać światła
  prepareDebugWindow(id);

  glClear(GL_DEPTH_BUFFER_BIT);

  mProgram->use();

  mVAO->bind();

  LightSpot *light = mEngine->getLightSystem()->mLightsSpot[id].get();

  CameraPerspective cam = *(light->getShadowCamera());

  light->getShadowTexture()->bind(GLint(FILLWAVE_SHADOW_FIRST_UNIT + id));

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
  mSampler->bind();
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

