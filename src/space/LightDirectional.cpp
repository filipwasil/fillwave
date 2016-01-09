/*
 * LightDirectional.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: filip
 */

#include <fillwave/space/LightDirectional.h>
#include <fillwave/loaders/ProgramLoader.h>

FLOGINIT("DirectionalLight", FERROR | FFATAL)

namespace fillwave {
namespace framework {

LightDirectional::LightDirectional(
		pTexture2DRenderable shadowTexture,
		glm::vec3 position,
		glm::quat rotation,
		glm::vec4 intensity,
		pMoveable followed)
		:
				Light(position, intensity, followed),
				mShadowTexture(shadowTexture),
				mShadowCamera(
						pCameraOrthographic(
								new CameraOrthographic(position, rotation, -10.0f,
										10.0f, 10.0f, -10.0f, 0.1f, 1000.0f))) {
}

pCameraOrthographic LightDirectional::getShadowCamera() {
	return mShadowCamera;
}

pTexture2DRenderable LightDirectional::getShadowTexture() {
	return mShadowTexture;
}

void LightDirectional::updateShadowCamera() {
	if (mShadowCamera->getTranslation() != mTranslation) {
		mShadowCamera->moveTo(mTranslation);
		mShadowCamera->update();
	}
	if (mShadowCamera->getRotation() != mRotation) {
		mShadowCamera->rotateTo(mRotation);
		mShadowCamera->update();
	}
}

/* Camera */
void LightDirectional::log() {
	auto d = [] (GLfloat f) { return static_cast<double>(f); };
	FLOG_INFO("mShadowCamera->getTranslation(): :%f :%f :%f",
			d(mShadowCamera->getTranslation().x), d(mShadowCamera->getTranslation().y),
			d(mShadowCamera->getTranslation().z));
	FLOG_INFO("mShadowCamera[0]: :%f :%f :%f :%f", d(mShadowCamera->getEye()[0].x),
			d(mShadowCamera->getEye()[0].y), d(mShadowCamera->getEye()[0].z),
			d(mShadowCamera->getEye()[0].w));
	FLOG_INFO("mShadowCamera[1]: :%f :%f :%f :%f", d(mShadowCamera->getEye()[1].x),
			d(mShadowCamera->getEye()[1].y), d(mShadowCamera->getEye()[1].z),
			d(mShadowCamera->getEye()[1].w));
	FLOG_INFO("mShadowCamera[2]: :%f :%f :%f :%f", d(mShadowCamera->getEye()[2].x),
			d(mShadowCamera->getEye()[2].y), d(mShadowCamera->getEye()[2].z),
			d(mShadowCamera->getEye()[2].w));
	FLOG_INFO("mShadowCamera[3]: :%f :%f :%f :%f", d(mShadowCamera->getEye()[3].x),
			d(mShadowCamera->getEye()[3].y), d(mShadowCamera->getEye()[3].z),
			d(mShadowCamera->getEye()[3].w));
	FLOG_INFO("Light mIntensity: R:%f G:%f B:%f A:%f", d(mIntensity.x),
			d(mIntensity.y), d(mIntensity.z), d(mIntensity.w));
}

} /* framework */
} /* fillwave */
