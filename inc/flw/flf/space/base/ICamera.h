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

#include <flw/flf/models/base/Moveable.h>
#include <flw/Math.h>
#include <memory>

namespace flw {
namespace flf {

/*! \class ICamera
 * \brief Stores camera view parameters.
 */

class ICamera : public Moveable {
public:
  ICamera();

  ICamera(glm::vec3 position, glm::quat rotation);

  ~ICamera() override;

  ICamera(const ICamera& arg);

  ICamera& operator=(const ICamera&);

  ICamera (ICamera&&);

  ICamera& operator=(ICamera &&);


  void update();

  void updateView();

  glm::mat4 getEye() const;

  glm::mat4 getProjection() const;

  glm::mat4 getViewProjection() const;

  virtual void updateProjection() = 0;

  virtual GLfloat getProjectionNearPlane() const = 0;

  virtual GLfloat getProjectionFarPlane() const = 0;

  virtual void log() const;

protected:
  glm::mat4 mCameraMatrix;
  glm::mat4 mProjectionMatrix;

  bool mRefreshView;
  bool mRefreshProjection;
};

} /* flf */
} /* flw */
