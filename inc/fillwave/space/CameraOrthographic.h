#pragma once

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

namespace flw {
namespace flf {

/*! \class CullingBox
 * \brief Stores culling box parameters for Orthographic projection.
 */

struct CullingBox {
  GLfloat mProjectionLeft;
  GLfloat mProjectionRight;
  GLfloat mProjectionBottom;
  GLfloat mProjectionTop;
  GLfloat mProjectionNear;
  GLfloat mProjectionFar;
};

/*! \class CameraOrthographic
 * \brief Camera with Orthographic projection.
 */

class CameraOrthographic : public ICamera {
public:
  CameraOrthographic();

  CameraOrthographic(glm::vec3 position,
      glm::quat rotation,
      GLfloat left,
      GLfloat right,
      GLfloat bottom,
      GLfloat top,
      GLfloat near,
      GLfloat far);

  ~CameraOrthographic() override = default;

  CameraOrthographic(const CameraOrthographic& camera) = default;

  CameraOrthographic& operator= (const CameraOrthographic& camera) = default;

  void updateProjection() override;

  GLfloat getProjectionNearPlane() override;

  GLfloat getProjectionFarPlane() override;

private:
  CullingBox mCullingBox;
};

} /* flf */
} /* flw */
