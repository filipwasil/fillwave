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

ICamera::~ICamera() = default;

ICamera::ICamera(const ICamera&) = default;

ICamera& ICamera::operator=(const ICamera&) = default;

ICamera::ICamera (ICamera&&) = default;

ICamera& ICamera::operator=(ICamera &&) = default;

inline void ICamera::updateView() {
  updateMatrixCache();

  mCameraMatrix = glm::lookAt(mTranslation,
                              mTranslation + glm::vec3((glm::mat4_cast(mRotation) * glm::vec4(0.0, 0.0, -1.0, 1.0))),
                              glm::vec3((glm::mat4_cast(mRotation) * glm::vec4(0.0, 1.0, 0.0, 1.0))));

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
