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

#include <fillwave/space/CameraPerspective.h>

namespace flw {
namespace flf {

CameraPerspective::CameraPerspective()
  : mProjectionFovy(glm::radians(90.0f))
  , mProjectionAspectRatio(1.0f)
  , mProjectionNearPlane(0.01f)
  , mProjectionFarPlane(100.0f) {
  updateProjection();
}

CameraPerspective::CameraPerspective(glm::vec3 position,
  glm::quat rotation,
  GLfloat fovy,
  GLfloat aspectRatio,
  GLfloat nearPlane,
  GLfloat farPlane)
  : ICamera(position, rotation)
  , mProjectionFovy(fovy)
  , mProjectionAspectRatio(aspectRatio)
  , mProjectionNearPlane(nearPlane)
  , mProjectionFarPlane(farPlane) {
  updateProjection();
}

void CameraPerspective::updateProjection() {
  mProjectionMatrix = glm::perspective(
    mProjectionFovy
    , mProjectionAspectRatio
    , mProjectionNearPlane
    , mProjectionFarPlane
  );
  mRefreshProjection = false;
}

GLfloat CameraPerspective::getProjectionFovy() const {
  return mProjectionFovy;
}

GLfloat CameraPerspective::getProjectionAspectRatio() const {
  return mProjectionAspectRatio;
}

GLfloat CameraPerspective::getProjectionNearPlane() const {
  return mProjectionNearPlane;
}

GLfloat CameraPerspective::getProjectionFarPlane() const {
  return mProjectionFarPlane;
}

void CameraPerspective::setProjectionFovy(GLfloat fovy) {
  mProjectionFovy = fovy;
  mRefreshProjection = true;
}

void CameraPerspective::setProjectionAspectRatio(GLfloat aspect) {
  mProjectionAspectRatio = aspect;
  mRefreshProjection = true;
}

void CameraPerspective::setProjectionNearPlane(GLfloat nearPlane) {
  mProjectionNearPlane = nearPlane;
  mRefreshProjection = true;
}

void CameraPerspective::setProjectionFarPlane(GLfloat farPlane) {
  mProjectionFarPlane = farPlane;
  mRefreshProjection = true;
}

} /* flf */
} /* flw */
