/*
 * Camera.cpp
 *
 *  Created on: May 7, 2014
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


#include <fillwave/space/base/ICamera.h>
#include <fillwave/Log.h>

FLOGINIT("Camera", FERROR | FFATAL | FINFO)

namespace flw {
namespace flf {

ICamera::ICamera(glm::vec3 position, glm::quat rotation)
    : Moveable(position, rotation), mRefreshView(GL_TRUE), mRefreshProjection(GL_TRUE) {
  updateView();
}

ICamera::ICamera()
    : Moveable(glm::vec3(0.0, 0.0, 1.0)), mRefreshView(GL_TRUE), mRefreshProjection(GL_TRUE) {
  updateView();
}

inline void ICamera::updateView() {
  updateMatrixCache();

  mCameraMatrix = glm::lookAt(mTranslation,
                              mTranslation + (glm::mat4_cast(mRotation) * glm::vec4(0.0, 0.0, -1.0, 1.0)).xyz(),
                              (glm::mat4_cast(mRotation) * glm::vec4(0.0, 1.0, 0.0, 1.0)).xyz());

  mRefreshView = GL_FALSE;
  mRefresh = GL_FALSE;
}

void ICamera::update() {
  if (mRefreshProjection) {
    fLogD("Camera projection update");
    updateProjection();
  }

  if (mRefresh || mRefreshView) {
    updateView();
  }
}

void ICamera::log() const {
  auto d = [](GLfloat f) {
    return static_cast<double>(f);
  };
  fLogI("Position: %f %f %f", d(mTranslation[0]), d(mTranslation[1]), d(mTranslation[2]));
//	fLogI("Camera rotation: %f %f %f %f ", d(mRotation[0]), d(mRotation[1]),
//			d(mRotation[2]), d(mRotation[4]));
}

glm::mat4 ICamera::getEye() {
  return mCameraMatrix;
}

glm::mat4 ICamera::getProjection() {
  return mProjectionMatrix;
}

glm::mat4 ICamera::getViewProjection() {
  return mProjectionMatrix * mCameraMatrix;
}

} /* flf */
} /* flw */
