#pragma once

/*
 * CameraPerspective.h
 *
 *  Created on: Dec 21, 2014
 *      Author: Filip Wasil
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

namespace flw {
namespace flf {

/*! \class CameraPerspective
 * \brief Camera with perspective projection.
 */

class CameraPerspective : public ICamera {
private:
  GLfloat mProjectionFovy, mProjectionAspectRatio, mProjectionNearPlane, mProjectionFarPlane;

public:
  CameraPerspective();

  CameraPerspective(glm::vec3 position,
      glm::quat rotation,
      GLfloat fovy = glm::radians(90.0f),
      GLfloat aspectRatio = 1.0f,
      GLfloat nearPlane = 0.01f,
      GLfloat farPlane = 100.0f);

  virtual ~CameraPerspective() = default;

  GLfloat getProjectionFovy();

  GLfloat getProjectionAspectRatio();

  GLfloat getProjectionNearPlane();

  GLfloat getProjectionFarPlane();

  void setProjectionFovy(GLfloat fovy);

  void setProjectionAspectRatio(GLfloat aspect);

  void setProjectionNearPlane(GLfloat nearPlane);

  void setProjectionFarPlane(GLfloat farPlane);

  void updateProjection();
};
} /* flf */
typedef std::unique_ptr<flf::CameraPerspective> puCameraPerspective;
} /* flw */
