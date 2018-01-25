#pragma once

/*
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

#include <fillwave/models/effects/Effect.h>

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
