/*
 * LightManager.h
 *
 *  Created on: 18 Apr 2013
 *      Author: Filip Wasil
 */

#ifndef LIGHTMANAGER_H_
#define LIGHTMANAGER_H_

#include <fillwave/space/LightDirectional.h>
#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class LightManager
 * \brief Manager to handle Light objects.
 */

#define FILLWAVE_MAX_SPOT_LIGHTS 4
#define FILLWAVE_MAX_POINT_LIGHTS 4
#define FILLWAVE_MAX_DIRECTIONAL_LIGHTS 4

class LightManager {
public:
	LightManager();
	virtual ~LightManager() = default;

	GLboolean isLightsRefresh();
	void resetLightsRefresh();
	void removeLights();
	void updateLightEntities();

	void pushLightUniformsDR();
	void pushLightUniforms(core::Program* program);
	void pushLightUniformBuffers(core::Program* program);

	pLightSpot addLightSpot(
			pTexture2DRenderable shadowTexture,
			glm::vec3 position,
			glm::quat rotation,
			glm::vec4 color,
			pMoveable followed = pMoveable());

	pLightPoint addLightPoint(
			pTexture3DRenderable shadowTexture,
			glm::vec3 position,
			glm::vec4 intensity,
			pMoveable followed = pMoveable());

	pLightDirectional addLightDirectional(
			pTexture2DRenderable shadowTexture,
			glm::vec3 position,
			glm::quat rotation,
			glm::vec4 color,
			pMoveable followed = pMoveable());

	void removeLight(pLightSpot light);
	void removeLight(pLightDirectional light);
	void removeLight(pLightPoint light);

	pLightSpot getLightSpot(GLint i);
	pLightPoint getLightPoint(GLint i);
	pLightDirectional getLightDirectional(GLint i);

	GLint getLightsSpotHowMany();
	GLint getLightsDirectionalHowMany();
	GLint getLightsPointHowMany();

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

	std::vector<pLightSpot> mSpotLights;
	std::vector<pLightDirectional> mDirectionalLights;
	std::vector<pLightPoint> mPointLights;
	std::vector<LighUniformData> mLightBufferData;

	GLboolean isRefreshLightSpot();
	GLboolean isRefreshLightDirectional();
	GLboolean isRefreshLightPoint();

	GLfloat computePointLightBoundingSphere(pLightPoint& light);
};

} /* framework */
typedef std::unique_ptr<framework::LightManager> puLightManager;
} /* fillwave*/

#endif /* LIGHTMANAGER_H_ */
