/*
 * Light.h
 *
 *  Created on: 17 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/models/Moveable.h>

namespace fillwave {
namespace space {

#define MAX_LIGHTS       4
#define USED_LIGHT_SLOTS 4
#if(USED_LIGHT_SLOTS > MAX_LIGHTS)
#error "used light slots can not be grater than available lights"
#endif

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

class Light: public models::Moveable {
public:
	Light(glm::vec3 position, glm::vec4 intensity, pMoveable followed = pMoveable());
	virtual ~Light() = default;

	void updateFromFollowed();

	void setAttenuation(LightAttenuationData& attenuation);

	LightAttenuationData getAttenuation();

	void setIntensity(glm::vec4 intensity);
	glm::vec4 getIntensity();
	void log();

protected:
	pMoveable mFollowed;
	glm::vec4 mIntensity;
	LightAttenuationData mAttenuation;
};

} /* space */
typedef std::shared_ptr<space::Light> pLight;
} /* fillwave */

#endif /* LIGHT_H_ */
