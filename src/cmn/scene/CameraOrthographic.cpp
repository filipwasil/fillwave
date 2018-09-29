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

#include <flw/cmn/scene/CameraOrthographic.h>

namespace flw {

CameraOrthographic::CameraOrthographic()
  : ICamera(glm::vec3(0.0f, 0.0f, 0.0f)
  , glm::quat()) {

  mCullingBox.mProjectionBottom = 10.0f;
  mCullingBox.mProjectionFar = 10.0f;
  mCullingBox.mProjectionLeft = 10.0f;
  mCullingBox.mProjectionNear = 10.0f;
  mCullingBox.mProjectionRight = 10.0f;
  mCullingBox.mProjectionTop = 10.0f;

  updateProjection();
}

CameraOrthographic::CameraOrthographic(
  glm::vec3 position
  , glm::quat rotation
  , GLfloat leftPlane
  , GLfloat rightPlane
  , GLfloat bottomPlane
  , GLfloat topPlane
  , GLfloat nearPlane
  , GLfloat farPlane)
  : ICamera(position, rotation) {

  mCullingBox.mProjectionBottom = bottomPlane;
  mCullingBox.mProjectionFar = farPlane;
  mCullingBox.mProjectionLeft = leftPlane;
  mCullingBox.mProjectionNear = nearPlane;
  mCullingBox.mProjectionRight = rightPlane;
  mCullingBox.mProjectionTop = topPlane;

  updateProjection();
}

void CameraOrthographic::updateProjection() {
  mProjectionMatrix = glm::ortho(
    mCullingBox.mProjectionLeft
    , mCullingBox.mProjectionRight
    , mCullingBox.mProjectionBottom
    , mCullingBox.mProjectionTop
    , mCullingBox.mProjectionNear
    , mCullingBox.mProjectionFar);

  mRefreshProjection = false;
}

GLfloat CameraOrthographic::getProjectionNearPlane() const {
  return mCullingBox.mProjectionNear;
}

GLfloat CameraOrthographic::getProjectionFarPlane() const {
  return mCullingBox.mProjectionFar;
}

} /* flw */

