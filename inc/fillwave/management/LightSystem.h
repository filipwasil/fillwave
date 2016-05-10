/*
 * LightManager.h
 *
 *  Created on: 18 Apr 2013
 *      Author: Filip Wasil
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

#ifndef LIGHTMANAGER_H_
#define LIGHTMANAGER_H_

#include <fillwave/management/base/TManager.h>
#include <fillwave/space/LightDirectional.h>
#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>

namespace fillwave {
class Engine;
namespace framework {

static constexpr size_t FILLWAVE_MAXIMUM_LIGHTS_IN_MANAGER = 4;

typedef TManager<LightSpot, FILLWAVE_MAXIMUM_LIGHTS_IN_MANAGER,
        core::Texture2DRenderable*, glm::vec3, glm::quat, glm::vec4, Moveable*>
        ManagerSpotLights;

typedef TManager<LightDirectional, FILLWAVE_MAXIMUM_LIGHTS_IN_MANAGER,
        core::Texture2DRenderable*, glm::vec3,
        glm::quat, glm::vec4, Moveable*> ManagerDirectionalLights;

typedef TManager<LightPoint, FILLWAVE_MAXIMUM_LIGHTS_IN_MANAGER,
        core::Texture3DRenderable*, glm::vec3, glm::vec4,
        Moveable*> ManagerPointLights;

/**
 * \brief Light system knows about all light related stuff.
 */
class LightSystem {
 public:
	LightSystem();
	virtual ~LightSystem() = default;

	ManagerSpotLights mLightsSpot;
	ManagerDirectionalLights mLightsDirectional;
	ManagerPointLights mLightsPoint;

	bool isLightsRefresh();
	void resetLightsRefresh();
	void removeLights();
	void updateLightEntities();

	void pushLightUniformsDR();
	void pushLightUniforms(core::Program* program);
	void pushLightUniformBuffers(core::Program* program);

	void clear();
	void bindShadowmaps();

	/* Deferred rendering */
	void updateDeferredBufferSpot(
	   GLuint lightID,
	   core::Program* program,
	   GLint currentShadowUnit);
	void updateDeferredBufferDirectional(
	   GLuint lightID,
	   core::Program* program,
	   GLint currentShadowUnit);
	void updateDeferredBufferPoint(
	   GLuint lightID,
	   core::Program* program,
	   GLint currentShadowUnit);

 private:
	std::vector<LighUniformData> mLightBufferData;

	GLboolean isRefreshLightSpot();
	GLboolean isRefreshLightDirectional();
	GLboolean isRefreshLightPoint();

	GLfloat computePointLightBoundingSphere(LightPoint* light);
};

} /* framework */
typedef std::unique_ptr<framework::LightSystem> puLightSystem;
} /* fillwave*/

#endif /* LIGHTMANAGER_H_ */
