/*
 * LightDirectional.h
 *
 *  Created on: Nov 30, 2014
 *      Author: filip
 */

#ifndef LIGHTDIRECTIONAL_H_
#define LIGHTDIRECTIONAL_H_

#include <fillwave/management/TextureSystem.h>
#include <fillwave/space/CameraOrthographic.h>
#include <fillwave/space/base/ILight.h>

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
class LightDirectional: public Light {
 public:
	LightDirectional(
	   core::Texture2DRenderable* shadowTexture,
	   glm::vec3 position,
	   glm::quat rotation,
	   glm::vec4 intensity,
	   pMoveable followed);
	virtual ~LightDirectional() = default;

	core::Texture2DRenderable* getShadowTexture();
	pCameraOrthographic getShadowCamera();

	void updateShadowCamera();

	void log();

 private:
	core::Texture2DRenderable* mShadowTexture;
	pCameraOrthographic mShadowCamera;
};

} /* framework */
typedef std::shared_ptr<framework::LightDirectional> pLightDirectional;
} /* fillwave */

#endif /* LIGHTDIRECTIONAL_H_ */
