/*
 * LightSpot.h
 *
 *  Created on: Nov 30, 2014
 *      Author: Filip Wasil
 */

#ifndef LIGHTSPOT_H_
#define LIGHTSPOT_H_

#include <fillwave/management/TextureSystem.h>
#include <fillwave/space/base/ILight.h>
#include <fillwave/space/CameraPerspective.h>

namespace fillwave {
namespace framework {

/*! \class LightSpot
 * \brief Light implementing directional torch.
 */

class LightSpot: public Light {
 protected:
	core::Texture2DRenderable* mShadowTexture;
	pCameraPerspective mShadowCamera;

 public:
	LightSpot(
	   core::Texture2DRenderable* shadowTexture,
	   glm::vec3 position,
	   glm::quat rotation,
	   glm::vec4 intensity,
	   pMoveable followed = pMoveable());

	virtual ~LightSpot() = default;

	core::Texture2DRenderable* getShadowTexture();

	pCameraPerspective getShadowCamera();

	void updateShadowCamera();

	void log();

};

} /* framework */
typedef framework::PtrShared<framework::LightSpot> pLightSpot;
} /* fillwave */

#endif /* LIGHTSPOT_H_ */
