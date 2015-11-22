/*
 * Light.cpp
 *
 *  Created on: 17 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/space/Light.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Light", FERROR | FFATAL)

namespace fillwave {
namespace space {

Light::Light(glm::vec3 position, glm::vec4 intensity, pMoveable followed)
		: Moveable(position), mFollowed(followed), mIntensity(intensity) {

}

void Light::updateFromFollowed() {
	if (mFollowed) {
		if (mFollowed->isRefresh()) {
			mTranslation = glm::vec3(
					mFollowed->getParentMMC()
							* glm::vec4(mFollowed->getTranslation(), 1.0));
			mRotation = glm::normalize(
					mFollowed->getParentRotation() * mFollowed->getRotation());
			mRefresh = GL_TRUE;
			mFollowed->setRefreshExternal(GL_FALSE);
		}
	}
}

void Light::setAttenuation(LightAttenuationData& attenuation) {
	mAttenuation = attenuation;
}

LightAttenuationData Light::getAttenuation() {
	return mAttenuation;
}

void Light::setIntensity(glm::vec4 intensity) {
	mIntensity = intensity;
	mRefresh = GL_TRUE;
}

glm::vec4 Light::getIntensity() {
	return mIntensity;
}

void Light::log() {
	auto d = [] (GLfloat& f) { return static_cast<double>(f); };
	FLOG_INFO("Light mIntensity: R:%f G:%f B:%f A:%f", d(mIntensity.x),
			d(mIntensity.y), d(mIntensity.z), d(mIntensity.w));
}

} /* space */
} /* fillwave */
