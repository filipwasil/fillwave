/*
 * LightManager.h
 *
 *  Created on: 18 Apr 2013
 *      Author: Filip Wasil
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

typedef TManager<pLightSpot, FILLWAVE_MAXIMUM_LIGHTS_IN_MANAGER, TPolicyShared<LightSpot>,
        core::Texture2DRenderable*, glm::vec3, glm::quat, glm::vec4, pMoveable>
        ManagerSpotLights;

typedef TManager<pLightDirectional, FILLWAVE_MAXIMUM_LIGHTS_IN_MANAGER,
        TPolicyShared<LightDirectional>, core::Texture2DRenderable*, glm::vec3,
        glm::quat, glm::vec4, pMoveable> ManagerDirectionalLights;

typedef TManager<pLightPoint, FILLWAVE_MAXIMUM_LIGHTS_IN_MANAGER,
        TPolicyShared<LightPoint>, core::Texture3DRenderable*, glm::vec3, glm::vec4,
        pMoveable> ManagerPointLights;

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

	GLfloat computePointLightBoundingSphere(pLightPoint& light);
};

} /* framework */
typedef std::unique_ptr<framework::LightSystem> puLightSystem;
} /* fillwave*/

#endif /* LIGHTMANAGER_H_ */
