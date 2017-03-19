/*
 * LightDirectional.h
 *
 *  Created on: Nov 30, 2014
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
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

#ifndef LIGHTDIRECTIONAL_H_
#define LIGHTDIRECTIONAL_H_

#include <fillwave/management/TextureSystem.h>
#include <fillwave/space/CameraOrthographic.h>
#include <fillwave/space/base/Light.h>

namespace fillwave {
class Engine;
namespace framework {

/**
 * \brief Light UBO data.
 */
struct LightDirectioData {
  GLfloat position[4];
  GLfloat intensity[4];
  GLfloat mvp[16];
};

/**
 * \brief Light with Orthographic projection.
 */
class LightDirectional : public Light {
public:
  LightDirectional(core::Texture2DRenderable *shadowTexture,
      glm::vec3 position,
      glm::quat rotation,
      glm::vec4 intensity,
      Moveable *followed = nullptr);

  virtual ~LightDirectional() = default;

  core::Texture2DRenderable *getShadowTexture();

  CameraOrthographic *getShadowCamera();

  void updateShadowCamera();

  void log();

private:
  core::Texture2DRenderable *mShadowTexture;
  puCameraOrthographic mShadowCamera;
};

} /* framework */
typedef std::unique_ptr<framework::LightDirectional> puLightDirectional;
} /* fillwave */

#endif /* LIGHTDIRECTIONAL_H_ */
