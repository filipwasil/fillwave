/*
 * LightPoint.h
 *
 *  Created on: Nov 30, 2014
 *      Author: Filip Wasil
 */

#ifndef LIGHTPOINT_H_
#define LIGHTPOINT_H_

#include <fillwave/core/rendering/Texture3DRenderable.h>
#include <fillwave/space/CameraPerspective.h>
#include <fillwave/models/shapes/Sphere.h>
#include <fillwave/space/Light.h>

#include <map>

namespace fillwave {
class Engine;
namespace space {

/*! \class LightPoint
 * \brief Not used.
 */

class LightPoint: public Light {
public:
	LightPoint(
			pTexture3DRenderable shadowTexture,
			glm::vec3 position,
			glm::vec4 intensity,
			pEntity entity = pEntity());

	virtual ~LightPoint() = default;

	pTexture3DRenderable getShadowTexture();

	pCameraPerspective getShadowCamera(GLenum id);

	void updateShadowCamera();

protected:
	pTexture3DRenderable mShadowTexture;
	std::map<GLenum, pCameraPerspective> mFaceCameras;

private:
	models::Sphere mSphere;
};

} /* space */
typedef std::shared_ptr<space::LightPoint> pLightPoint;
} /* fillwave */

#endif /* LIGHTPOINT_H_ */
