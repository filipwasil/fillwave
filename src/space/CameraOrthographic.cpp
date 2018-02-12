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

