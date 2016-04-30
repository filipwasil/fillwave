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
class LightDirectional: public Light {
 public:
	LightDirectional(
	   core::Texture2DRenderable* shadowTexture,
	   glm::vec3 position,
	   glm::quat rotation,
	   glm::vec4 intensity,
	   Moveable* followed = nullptr);
	virtual ~LightDirectional() = default;

	core::Texture2DRenderable* getShadowTexture();
	CameraOrthographic* getShadowCamera();

	void updateShadowCamera();

	void log();

 private:
	core::Texture2DRenderable* mShadowTexture;
	puCameraOrthographic mShadowCamera;
};

} /* framework */
typedef std::unique_ptr<framework::LightDirectional> puLightDirectional;
} /* fillwave */

#endif /* LIGHTDIRECTIONAL_H_ */
