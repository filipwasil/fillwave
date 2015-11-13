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

Light::Light(glm::vec3 position, glm::vec4 intensity, pEntity entity)
		: Moveable(position), mEntity(entity), mIntensity(intensity) {

}

void Light::updateEntity() {
	if (mEntity) {
		if (mEntity->isExternalRefresh()) {
			mTranslation = glm::vec3(
					mEntity->getParentMatrix()
							* glm::vec4(mEntity->getTranslation(), 1.0));
			mRotation = glm::normalize(
					mEntity->getParentRotation() * mEntity->getRotation());
			mRefresh = GL_TRUE;
			mEntity->setExternalRefresh(GL_FALSE);
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

void Light::setEntity(pEntity entity) {
	mRefresh = GL_TRUE;
	entity->setExternalRefresh(GL_TRUE);
	mEntity = entity;
}

pEntity Light::getEntity() {
	return mEntity;
}

void Light::log() {
	auto d = [] (GLfloat& f) { return static_cast<double>(f); };
	FLOG_INFO("Light mIntensity: R:%f G:%f B:%f A:%f", d(mIntensity.x),
			d(mIntensity.y), d(mIntensity.z), d(mIntensity.w));
}

} /* space */
} /* fillwave */
