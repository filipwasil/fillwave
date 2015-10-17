/*
 * LightSpot.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: filip
 */

#include <fillwave/space/LightSpot.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Spotlight", FERROR | FFATAL)

namespace fillwave {
namespace space {

LightSpot::LightSpot(
		pTexture2DRenderable shadowTexture,
		glm::vec3 position,
		glm::quat rotation,
		glm::vec4 intensity,
		pEntity entity)
		:
				Light(position, intensity, entity),
				mShadowTexture(shadowTexture),
				mShadowCamera(
						pCameraPerspective(
								new CameraPerspective(position, rotation,
										glm::radians(90.0), 1.0, //xxx fix
										0.1, 1000.0))) {
}

pTexture2DRenderable LightSpot::getShadowTexture() {
	return mShadowTexture;
}

/*
 * getShadowCamera
 * \brief get the shadow caster camera matrix
 */

pCameraPerspective LightSpot::getShadowCamera() {
	return mShadowCamera;
}

void LightSpot::updateShadowCamera() {
	if (mShadowCamera->getTranslation() != mTranslation) {
		mShadowCamera->moveTo(mTranslation);
		mShadowCamera->update();
	}
	if (mShadowCamera->getRotation() != mRotation) {
		mShadowCamera->rotateTo(mRotation);
		mShadowCamera->update();
	}
}

void LightSpot::log() {
	FLOG_INFO("mShadowCamera->getTranslation(): :%f :%f :%f",
			mShadowCamera->getTranslation().x, mShadowCamera->getTranslation().y,
			mShadowCamera->getTranslation().z);
	FLOG_INFO("mShadowCamera[0]: :%f :%f :%f :%f", mShadowCamera->getEye()[0].x,
			mShadowCamera->getEye()[0].y, mShadowCamera->getEye()[0].z,
			mShadowCamera->getEye()[0].w);
	FLOG_INFO("mShadowCamera[1]: :%f :%f :%f :%f", mShadowCamera->getEye()[1].x,
			mShadowCamera->getEye()[1].y, mShadowCamera->getEye()[1].z,
			mShadowCamera->getEye()[1].w);
	FLOG_INFO("mShadowCamera[2]: :%f :%f :%f :%f", mShadowCamera->getEye()[2].x,
			mShadowCamera->getEye()[2].y, mShadowCamera->getEye()[2].z,
			mShadowCamera->getEye()[2].w);
	FLOG_INFO("mShadowCamera[3]: :%f :%f :%f :%f", mShadowCamera->getEye()[3].x,
			mShadowCamera->getEye()[3].y, mShadowCamera->getEye()[3].z,
			mShadowCamera->getEye()[3].w);
	FLOG_INFO("Light mTranslation: X:%f Y:%f Z:%f", mTranslation.x,
			mTranslation.y, mTranslation.z);
	FLOG_INFO("Light mIntensity: R:%f G:%f B:%f A:%f", mIntensity.x,
			mIntensity.y, mIntensity.z, mIntensity.w);
	mEntity->log();
}

} /* space */
} /* fillwave */
