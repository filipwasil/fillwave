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

#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/models/base/Moveable.h>
#include <fillwave/common/IObserver.h>

namespace flw {
namespace flf {

constexpr size_t MAX_LIGHTS = 4;
constexpr size_t USED_LIGHT_SLOTS = 4;

/*! \struct LighUniformData
 * \brief Light UBO data.
 */

struct LighUniformData {
  GLfloat position[4];
  GLfloat intensity[4];
  GLfloat mvp[16];
};

/*! \struct LightAttenuationData
 * \brief Light attenuation data.
 */
struct LightAttenuationData {
  GLfloat mLinear;
  GLfloat mExp;
};

/*! \class Light
 * \brief Base for all lights.
 */

class Light : public Moveable, public IObserver {
public:
  Light(glm::vec3 pos, glm::vec4 intensity, Moveable* observed);

  ~Light() override;

  void updateFromFollowed();

  void setAttenuation(LightAttenuationData &attenuation);

  LightAttenuationData getAttenuation();

  void setIntensity(glm::vec4 intensity);

  glm::vec4 getIntensity();

  void log();

  void onDeath(Observable* observable) override;

  void onChanged(Observable* observable) override;

protected:
  Moveable* mObserved;
  bool mIsFollowedUpdated;
  glm::vec4 mIntensity;
  LightAttenuationData mAttenuation;
};

} /* flf */
} /* flw */
