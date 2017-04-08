/*
 * LightPoint.cpp
 *
 *  Created on: Nov 30, 2014
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


#include <fillwave/space/LightPoint.h>
#include <fillwave/Log.h>

FLOGINIT("LightPoint", FERROR | FFATAL)

namespace flw {
namespace flf {

LightPoint::LightPoint(flc::Texture3DRenderable *shadowTexture,
    glm::vec3 position,
    glm::vec4 intensity,
    Moveable *followed)
    : Light(position, intensity, followed), mShadowTexture(shadowTexture), mSphere(1.0, 10, 10) {
  mFaceCameras[GL_TEXTURE_CUBE_MAP_POSITIVE_X] = std::make_unique<CameraPerspective>(position,
                                                                                     glm::normalize(
                                                                                         glm::angleAxis(glm::radians(
                                                                                             90.0f),
                                                                                                        glm::normalize(
                                                                                                            glm::vec3(
                                                                                                                0.0,
                                                                                                                1.0,
                                                                                                                0.0))) *
                                                                                         glm::angleAxis(glm::radians(
                                                                                             180.0f),
                                                                                                        glm::normalize(
                                                                                                            glm::vec3(
                                                                                                                1.0,
                                                                                                                0.0,
                                                                                                                0.0)))),
                                                                                     glm::radians(90.0),
                                                                                     1.0, //1440.0/900.0,
                                                                                     0.1,
                                                                                     1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_NEGATIVE_X] = std::make_unique<CameraPerspective>(
      position,
      glm::normalize(glm::angleAxis(glm::radians(-90.0f), glm::normalize(glm::vec3(0.0, 1.0, 0.0))) *
                     glm::angleAxis(glm::radians(180.0f), glm::normalize(glm::vec3(1.0, 0.0, 0.0)))),
      glm::radians(90.0),
      1.0, //1440.0/900.0,
      0.1,
      1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_POSITIVE_Y] = std::make_unique<CameraPerspective>(position,
                                                                                                  glm::normalize(glm::angleAxis(
                                                                                                      glm::radians(90.0f),
                                                                                                      glm::normalize(glm::vec3(
                                                                                                          1.0,
                                                                                                          0.0,
                                                                                                          0.0)))),
                                                                                                  glm::radians(90.0),
                                                                                                  1.0, //1440.0/900.0,
                                                                                                  0.1,
                                                                                                  1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_NEGATIVE_Y] = std::make_unique<CameraPerspective>(
      position,
      glm::normalize(glm::angleAxis(glm::radians(-90.0f), glm::normalize(glm::vec3(1.0, 0.0, 0.0)))),
      glm::radians(90.0),
      1.0, //1440.0/900.0,
      0.1,
      1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_POSITIVE_Z] = std::make_unique<CameraPerspective>(position,
                                                                                                  glm::normalize(glm::angleAxis(
                                                                                                      glm::radians(
                                                                                                          180.0f),
                                                                                                      glm::normalize(glm::vec3(
                                                                                                          0.0,
                                                                                                          0.0,
                                                                                                          1.0)))),
                                                                                                  glm::radians(90.0),
                                                                                                  1.0, //1440.0/900.0,
                                                                                                  0.1,
                                                                                                  1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_NEGATIVE_Z] = std::make_unique<CameraPerspective>(
      position,
      glm::normalize(glm::angleAxis(glm::radians(180.0f), glm::normalize(glm::vec3(0.0, 1.0, 0.0))) *
                     glm::angleAxis(glm::radians(180.0f), glm::normalize(glm::vec3(0.0, 0.0, 1.0)))),
      glm::radians(90.0),
      1.0, //1440.0/900.0,
      0.1,
      1000.0);
}

flc::Texture3DRenderable *LightPoint::getShadowTexture() {
  return mShadowTexture;
}

CameraPerspective *LightPoint::getShadowCamera(GLenum id) {
  if (mFaceCameras.count(id) == 1) {
    return mFaceCameras[id].get();
  } else {
    fLogF("Can not get shadow camera. This should never happen. Good bye ...");
    return nullptr;
  }
}

void LightPoint::updateShadowCamera() {
  if (mFollowed) {
    mTranslation = mFollowed->getTranslation();
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
