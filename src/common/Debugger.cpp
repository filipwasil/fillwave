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


namespace fillwave {
namespace framework {

Debugger::Debugger(Engine *engine)
    : IReloadable (engine), mState (eDebuggerState::eOff), mEngine (engine)
    , mVBO (mEngine->storeBuffer<core::VertexBufferDebug> (mVAO, 1.0f)), mMiniwindowSize (1.0 / 6.0)
    , mMiniwindowsOccupied (0) {

  ProgramLoader loader (engine);

  mProgram = loader.getDebugger ();

  initPipeline ();
  initVBO ();
  initVAO ();
  initUniformsCache ();
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

void Debugger::setMiniwindowSize(GLfloat size) {
  mMiniwindowSize = size;
}

void Debugger::renderFromCamera(ICamera &c, GLint id) {
  glViewport (mEngine->getScreenSize ()[0] * (id) * mMiniwindowSize,
              mEngine->getScreenSize ()[1] * (1.0f - mMiniwindowSize),
              mEngine->getScreenSize ()[0] * mMiniwindowSize,
              mEngine->getScreenSize ()[1] * mMiniwindowSize);

  glClear (GL_DEPTH_BUFFER_BIT);

  mEngine->getCurrentScene ()->draw (c);

  glViewport (0, 0, mEngine->getScreenSize ()[0], mEngine->getScreenSize ()[1]);
}

void Debugger::renderPickingMap() {
  glViewport (mEngine->getScreenSize ()[0] * (1.0f - mMiniwindowSize),
              0,
              mEngine->getScreenSize ()[0] * mMiniwindowSize,
              mEngine->getScreenSize ()[1] * mMiniwindowSize);

  glClear (GL_DEPTH_BUFFER_BIT);
  mEngine->getCurrentScene ()->drawPicking ();
  glViewport (0, 0, mEngine->getScreenSize ()[0], mEngine->getScreenSize ()[1]);
}

void Debugger::renderDepthOrthographic(GLint id) { //xxx ujednolicić to całe lightID żeby można było usuwać światła
  glViewport (mEngine->getScreenSize ()[0] * (id) * mMiniwindowSize,
              0,
              mEngine->getScreenSize ()[0] * mMiniwindowSize,
              mEngine->getScreenSize ()[1] * mMiniwindowSize);

  glClear (GL_DEPTH_BUFFER_BIT);

  mProgram->use ();

  mVAO->bind ();

  LightDirectional *light = mEngine->getLightSystem ()->mLightsDirectional[id].get ();

  ICamera *cam = light->getShadowCamera ();

  light->getShadowTexture ()->bind (GLint (FILLWAVE_SHADOW_FIRST_UNIT + id));

  glDisable (GL_DEPTH_TEST);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  core::Uniform::push (mULCTextureUnit, id);
  core::Uniform::push (mULCNearPlane, cam->getProjectionNearPlane ());
  core::Uniform::push (mULCFarPlane, cam->getProjectionFarPlane ());

  glDrawArrays (GL_TRIANGLES, 0, mVBO->getElements ());

  glEnable (GL_DEPTH_TEST);
  glDisable (GL_BLEND);

  core::Texture2D::unbind2DTextures ();
  core::VertexArray::unbindVAO ();
  core::Program::disusePrograms ();

  glViewport (0, 0, mEngine->getScreenSize ()[0], mEngine->getScreenSize ()[1]);
}

void Debugger::renderDepthPerspective(GLint id) { //xxx ujednolicić to całe lightID żeby można było usuwać światła
  glViewport (mEngine->getScreenSize ()[0] * (id) * mMiniwindowSize,
              0,
              mEngine->getScreenSize ()[0] * mMiniwindowSize,
              mEngine->getScreenSize ()[1] * mMiniwindowSize);

  glClear (GL_DEPTH_BUFFER_BIT);

  mProgram->use ();

  mVAO->bind ();

  LightSpot *light = mEngine->getLightSystem ()->mLightsSpot[id].get ();

  CameraPerspective cam = *(light->getShadowCamera ());

  light->getShadowTexture ()->bind (GLint (FILLWAVE_SHADOW_FIRST_UNIT + id));

  glDisable (GL_DEPTH_TEST);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  core::Uniform::push (mULCTextureUnit, FILLWAVE_SHADOW_FIRST_UNIT + id);
  core::Uniform::push (mULCNearPlane, cam.getProjectionNearPlane ());
  core::Uniform::push (mULCFarPlane, cam.getProjectionFarPlane ());

  glDrawArrays (GL_TRIANGLES, 0, mVBO->getElements ());

  glEnable (GL_DEPTH_TEST);
  glDisable (GL_BLEND);

  core::Texture2D::unbind2DTextures ();
  core::VertexArray::unbindVAO ();
  core::Program::disusePrograms ();

  glViewport (0, 0, mEngine->getScreenSize ()[0], mEngine->getScreenSize ()[1]);
}

inline void Debugger::initBuffers() {
  if (mVBO) {
    mVBO->reload ();
  }
}

inline void Debugger::initPipeline() {

}

inline void Debugger::initUniformsCache() {
  mULCTextureUnit = mProgram->getUniformLocation ("uTextureUnit");
  mULCNearPlane = mProgram->getUniformLocation ("uNearplane");
  mULCFarPlane = mProgram->getUniformLocation ("uFarPlane");
}

inline void Debugger::initVAO() {
  mSampler->bind ();
  mVAO->bind ();

  mVBO->bind ();
  mVBO->setLoaded (GL_FALSE);
  mVBO->send ();
  mVBO->attributesSetForVAO ();

  core::VertexArray::unbindVAO ();
}

inline void Debugger::initVBO() {
  mVBO->initAttributes (mProgram->getHandle ());
}

} /* framework */
} /* fillwave */

