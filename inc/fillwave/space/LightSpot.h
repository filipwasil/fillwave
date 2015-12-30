/*
 * LightSpot.h
 *
 *  Created on: Nov 30, 2014
 *      Author: Filip Wasil
 */

#ifndef LIGHTSPOT_H_
#define LIGHTSPOT_H_

#include <fillwave/space/Light.h>
#include <fillwave/space/CameraPerspective.h>
#include <fillwave/management/TextureManager.h>

namespace fillwave {
namespace framework {

/*! \class LightSpot
 * \brief Light implementing directional torch.
 */

class LightSpot: public Light {
protected:
	pTexture2DRenderable mShadowTexture;
	pCameraPerspective mShadowCamera;

public:
	LightSpot(
			pTexture2DRenderable shadowTexture,
			glm::vec3 position,
			glm::quat rotation,
			glm::vec4 intensity,
			pMoveable followed = pMoveable());

	virtual ~LightSpot() = default;

	pTexture2DRenderable getShadowTexture();

	pCameraPerspective getShadowCamera();

	void updateShadowCamera();

	void log();

};

} /* framework */
typedef std::shared_ptr<framework::LightSpot> pLightSpot;
} /* fillwave */

#endif /* LIGHTSPOT_H_ */
