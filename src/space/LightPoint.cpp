/*
 * LightPoint.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
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


#include <fillwave/space/LightPoint.h>
#include <fillwave/Log.h>

FLOGINIT("LightPoint", FERROR | FFATAL)

namespace flw {
namespace flf {

LightPoint::LightPoint(flc::Texture3DRenderable* tex, glm::vec3 pos, glm::vec4 intensity, Moveable* observed)
    : Light(pos, intensity, observed)
    , mShadowTexture(tex)
    , mSphere(1.0f, 10, 10) {
  const glm::vec3 axisX(1.0f, 0.0f, 0.0f);
  const glm::vec3 axisY(0.0f, 1.0f, 0.0f);
  const glm::vec3 axisZ(0.0f, 0.0f, 1.0f);
  mFaceCameras[GL_TEXTURE_CUBE_MAP_POSITIVE_X] = std::make_unique<CameraPerspective>(
    pos
    , glm::normalize(glm::angleAxis(glm::radians(90.0f), axisY) * glm::angleAxis(glm::radians(180.0f), axisX))
    , glm::radians(90.0f), 1.0f, 0.1f, 1000.0f);
  mFaceCameras[GL_TEXTURE_CUBE_MAP_NEGATIVE_X] = std::make_unique<CameraPerspective>(
    pos
    , glm::normalize(glm::angleAxis(glm::radians(-90.0f), axisY) * glm::angleAxis(glm::radians(180.0f), axisX))
    , glm::radians(90.0f), 1.0f, 0.1f, 1000.0f);
  mFaceCameras[GL_TEXTURE_CUBE_MAP_POSITIVE_Y] = std::make_unique<CameraPerspective>(
    pos
    , glm::normalize(glm::angleAxis(glm::radians(90.0f), axisX))
    , glm::radians(90.0f), 1.0f, 0.1f, 1000.0f);
  mFaceCameras[GL_TEXTURE_CUBE_MAP_NEGATIVE_Y] = std::make_unique<CameraPerspective>(
    pos
    , glm::normalize(glm::angleAxis(glm::radians(-90.0f), axisX))
    , glm::radians(90.0f), 1.0f, 0.1f, 1000.0f);
  mFaceCameras[GL_TEXTURE_CUBE_MAP_POSITIVE_Z] = std::make_unique<CameraPerspective>(
    pos
    , glm::normalize(glm::angleAxis(glm::radians(180.0f), axisZ))
    , glm::radians(90.0f), 1.0f, 0.1f, 1000.0f);
  mFaceCameras[GL_TEXTURE_CUBE_MAP_NEGATIVE_Z] = std::make_unique<CameraPerspective>(
    pos
    , glm::normalize(glm::angleAxis(glm::radians(180.0f), axisY) * glm::angleAxis(glm::radians(180.0f), axisZ))
    , glm::radians(90.0f), 1.0f, 0.1f, 1000.0f);
}

flc::Texture3DRenderable* LightPoint::getShadowTexture() {
  return mShadowTexture;
}

CameraPerspective* LightPoint::getShadowCamera(GLenum id) {
  if (mFaceCameras.count(id) == 1) {
    return mFaceCameras[id].get();
  }
  fLogF("Can not get shadow camera. This should never happen. Good bye ...");
  return nullptr;
}

void LightPoint::updateShadowCamera() {
  if (mObserved) {
    mTranslation = mObserved->getTranslation();
  }
  for (auto &it : mFaceCameras) {
    if (it.second->getTranslation() != mTranslation) {
      it.second->moveTo(mTranslation);
      it.second->update();
    }
  }
}

} /* flf */
} /* flw */
