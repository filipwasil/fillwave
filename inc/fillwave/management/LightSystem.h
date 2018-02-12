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

#include <fillwave/management/base/TCacheVector.h>
#include <fillwave/space/LightDirectional.h>
#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>

namespace flw {
class Engine;
namespace flf {

using CacheSpotLights = TManager<LightSpot, MAX_LIGHTS, flc::Texture2DRenderable*, glm::vec3, glm::quat, glm::vec4, flf::Moveable*>;
using CacheDirectionalLights = TManager<LightDirectional, MAX_LIGHTS, flc::Texture2DRenderable*, glm::vec3, glm::quat, glm::vec4, flf::Moveable*>;
using CachePointLights = TManager<LightPoint, MAX_LIGHTS, flc::Texture3DRenderable*, glm::vec3, glm::vec4, flf::Moveable*>;

/**
 * \brief Light system knows about all light related stuff.
 */
class LightSystem final {
public:
  LightSystem();

  CacheSpotLights mLightsSpot;
  CacheDirectionalLights mLightsDirectional;
  CachePointLights mLightsPoint;

  bool isLightsRefresh();

  void resetLightsRefresh();

  void removeLights();

  void updateLightEntities();

  void pushLightUniformsDR();

  void pushLightUniforms(flc::Program *program);

  void pushLightUniformBuffers(flc::Program *program);

  void clear();

  void bindShadowmaps();

  /* Deferred rendering */
  void updateDeferredBufferSpot(GLuint lightID, flc::Program *program, GLint currentShadowUnit);

  void updateDeferredBufferDirectional(GLuint lightID, flc::Program *program, GLint currentShadowUnit);

  void updateDeferredBufferPoint(GLuint lightID, flc::Program *program, GLint currentShadowUnit);

private:
  std::vector<LighUniformData> mLightBufferData;

  GLboolean isRefreshLightSpot();

  GLboolean isRefreshLightDirectional();

  GLboolean isRefreshLightPoint();

  GLfloat computePointLightBoundingSphere(LightPoint *light);
};

} /* flf */
} /* flw */
