/*
 * CameraOrthographic.cpp
 *
 *  Created on: Dec 21, 2014
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


#include <fillwave/space/CameraOrthographic.h>

namespace flw {
namespace flf {

CameraOrthographic::CameraOrthographic()
    : ICamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat()) {

  mCullingBox.mProjectionBottom = 10.0f;
  mCullingBox.mProjectionFar = 10.0f;
  mCullingBox.mProjectionLeft = 10.0f;
  mCullingBox.mProjectionNear = 10.0f;
  mCullingBox.mProjectionRight = 10.0f;
  mCullingBox.mProjectionTop = 10.0f;

  updateProjection();
}

CameraOrthographic::CameraOrthographic(glm::vec3 position,
    glm::quat rotation,
    GLfloat left,
    GLfloat right,
    GLfloat bottom,
    GLfloat top,
    GLfloat near,
    GLfloat far)
    : ICamera(position, rotation) {

  mCullingBox.mProjectionBottom = bottom;
  mCullingBox.mProjectionFar = far;
  mCullingBox.mProjectionLeft = left;
  mCullingBox.mProjectionNear = near;
  mCullingBox.mProjectionRight = right;
  mCullingBox.mProjectionTop = top;

  updateProjection();
}

void CameraOrthographic::updateProjection() {
  mProjectionMatrix = glm::ortho(mCullingBox.mProjectionLeft,
                                 mCullingBox.mProjectionRight,
                                 mCullingBox.mProjectionBottom,
                                 mCullingBox.mProjectionTop,
                                 mCullingBox.mProjectionNear,
                                 mCullingBox.mProjectionFar);

  mRefreshProjection = GL_FALSE;
}

GLfloat CameraOrthographic::getProjectionNearPlane() {
  return mCullingBox.mProjectionNear;
}

GLfloat CameraOrthographic::getProjectionFarPlane() {
  return mCullingBox.mProjectionFar;
}

} /* flf */
} /* flw */

