/*
 * LightSpot.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: filip
 */

#include <fillwave/space/LightSpot.h>
#include <fillwave/Log.h>

FLOGINIT("Spotlight", FERROR | FFATAL)

namespace fillwave {
namespace framework {

LightSpot::LightSpot(
    core::Texture2DRenderable* shadowTexture,
    glm::vec3 position,
    glm::quat rotation,
    glm::vec4 intensity,
    pMoveable followed) :
	Light(position, intensity, followed),
	mShadowTexture(shadowTexture),
	mShadowCamera(
	    std::make_shared < CameraPerspective
	    > (position, rotation, glm::radians(90.0f), 1.0f, //xxx fix
	       0.1f, 1000.0f)) {
}

core::Texture2DRenderable* LightSpot::getShadowTexture() {
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
	auto d = [] (GLfloat f) {
		return static_cast<double>(f);
	};
	FLOG_INFO("mShadowCamera->getTranslation(): :%f :%f :%f",
	          d(mShadowCamera->getTranslation().x),
	          d(mShadowCamera->getTranslation().y),
	          d(mShadowCamera->getTranslation().z));
	FLOG_INFO("mShadowCamera[0]: :%f :%f :%f :%f",
	          d(mShadowCamera->getEye()[0].x), d(mShadowCamera->getEye()[0].y),
	          d(mShadowCamera->getEye()[0].z), d(mShadowCamera->getEye()[0].w));
	FLOG_INFO("mShadowCamera[1]: :%f :%f :%f :%f",
	          d(mShadowCamera->getEye()[1].x), d(mShadowCamera->getEye()[1].y),
	          d(mShadowCamera->getEye()[1].z), d(mShadowCamera->getEye()[1].w));
	FLOG_INFO("mShadowCamera[2]: :%f :%f :%f :%f",
	          d(mShadowCamera->getEye()[2].x), d(mShadowCamera->getEye()[2].y),
	          d(mShadowCamera->getEye()[2].z), d(mShadowCamera->getEye()[2].w));
	FLOG_INFO("mShadowCamera[3]: :%f :%f :%f :%f",
	          d(mShadowCamera->getEye()[3].x), d(mShadowCamera->getEye()[3].y),
	          d(mShadowCamera->getEye()[3].z), d(mShadowCamera->getEye()[3].w));
	FLOG_INFO("Light mTranslation: X:%f Y:%f Z:%f", d(mTranslation.x),
	          d(mTranslation.y), d(mTranslation.z));
	FLOG_INFO("Light mIntensity: R:%f G:%f B:%f A:%f", d(mIntensity.x),
	          d(mIntensity.y), d(mIntensity.z), d(mIntensity.w));
	Light::log();
}

} /* framework */
} /* fillwave */
