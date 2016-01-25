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
	LightManager(GLsizei screenWidth, GLsizei screenHeight);
	virtual ~LightManager() = default;

	GLboolean isLightsRefresh();
	void resetLightsRefresh();

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
	void removeLights();

	GLint getLightsSpotHowMany();
	GLint getLightsDirectionalHowMany();
	GLint getLightsPointHowMany();

	void updateLightEntities();

	void pushLightUniformsDR();
	void pushLightUniforms(core::Program* program);
	void pushLightUniformBuffers(core::Program* program);

	void pushLightUniforms(GLuint program);
	void pushLightUniformBuffers(GLuint program);

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

	pLightSpot getLightSpot(GLint i);
	pLightPoint getLightPoint(GLint i);
	pLightDirectional getLightDirectional(GLint i);

	GLint obtainTextureUnit();
	void freeTextureUnit(GLint id);

	void bindShadowmaps();

private:
	const glm::mat4 mBiasMatrix = glm::mat4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0,
			0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);

	GLsizei mShadowWidth;
	GLsizei mShadowHeight;

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
