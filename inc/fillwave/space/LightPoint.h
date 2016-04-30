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
#include <fillwave/space/base/Light.h>

#include <map>

namespace fillwave {
class Engine;
namespace framework {

/*! \class LightPoint
 * \brief Not used.
 */

class LightPoint: public Light {
 public:
	LightPoint(
	   core::Texture3DRenderable* shadowTexture,
	   glm::vec3 position,
	   glm::vec4 intensity,
	   Moveable* followed = nullptr);

	virtual ~LightPoint() = default;

	core::Texture3DRenderable* getShadowTexture();

	CameraPerspective* getShadowCamera(GLenum id);

	void updateShadowCamera();

 protected:
	core::Texture3DRenderable* mShadowTexture;
	std::map<GLenum, puCameraPerspective> mFaceCameras;

 private:
	Sphere mSphere;
};

} /* framework */
typedef std::unique_ptr<framework::LightPoint> puLightPoint;
} /* fillwave */

#endif /* LIGHTPOINT_H_ */
