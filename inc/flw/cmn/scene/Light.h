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

#include <flw/flc/rendering/Texture2DRenderable.h>
#include <flw/cmn/scene/Moveable.h>
#include <flw/cmn/IObserver.h>

namespace flw {

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

  Light(const Light&) = delete;

  Light operator=(const Light&) = delete;

  void updateFromFollowed();

  void setAttenuation(LightAttenuationData &attenuation);

  LightAttenuationData getAttenuation();

  void setIntensity(glm::vec4 intensity);

  glm::vec4 getIntensity();

  void log();

  void onDestroy(Observable* observable) override;

  void onChanged(Observable* observable) override;

protected:
  Moveable* mObserved;
  bool mIsFollowedUpdated;
  glm::vec4 mIntensity;
  LightAttenuationData mAttenuation;
};

} /* flw */
