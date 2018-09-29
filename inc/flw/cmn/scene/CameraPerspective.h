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

#include <flw/cmn/scene/ICamera.h>

namespace flw {

/*! \class CameraPerspective
 * \brief Camera with perspective projection.
 */

class CameraPerspective : public ICamera {
private:
  GLfloat mProjectionFovy;
  GLfloat mProjectionAspectRatio;
  GLfloat mProjectionNearPlane;
  GLfloat mProjectionFarPlane;

public:
  CameraPerspective();

  CameraPerspective(glm::vec3 position,
      glm::quat rotation,
      GLfloat fovy = glm::radians(90.0f),
      GLfloat aspectRatio = 1.0f,
      GLfloat nearPlane = 0.01f,
      GLfloat farPlane = 100.0f);

  GLfloat getProjectionFovy() const;

  GLfloat getProjectionAspectRatio() const;

  GLfloat getProjectionNearPlane() const override;

  GLfloat getProjectionFarPlane() const override;

  void updateProjection() override;

  void setProjectionFovy(GLfloat fovy);

  void setProjectionAspectRatio(GLfloat aspect);

  void setProjectionNearPlane(GLfloat nearPlane);

  void setProjectionFarPlane(GLfloat farPlane);
};

} /* flw */
