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

#include <flw/flf/models/effects/IEffect.h>

namespace flw {
namespace flf {

/*! \class Fog
 * \brief Effect to create a fog.
 */

class Fog : public IEffect {
public:
  Fog(glm::vec3 colour = glm::vec3(0.1f, 0.1f, 0.1f), GLfloat near = 0.1f, GLfloat far = 20.0f);

  ~Fog() override = default;

  glm::vec3 getColour() {
    return mColour;
  }

  GLfloat getNearDistance() {
    return mNearDistance;
  }

  GLfloat getFarDistance() {
    return mFarDistance;
  }

  void setColour(glm::vec3 colour) {
    mColour = colour;
  }

  void setNearDistance(GLfloat aNear) {
    mNearDistance = aNear;
  }

  void setFarDistance(GLfloat aFar) {
    mFarDistance = aFar;
  }

  void preDrawAction(flc::Program* program) override;

  void postDrawAction(flc::Program* program) override;

  void stopAction(flc::Program* program) override;

  void startAction(flc::Program* program) override;

private:
  glm::vec3 mColour;
  GLfloat mNearDistance;
  GLfloat mFarDistance;
};

} /* flf */
} /* flw */
