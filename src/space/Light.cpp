/*
 * Light.cpp
 *
 *  Created on: 17 Apr 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/space/Light.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Light", FERROR | FFATAL)

namespace fillwave {
namespace space {

Light::Light(glm::vec3 position, glm::vec4 intensity, pEntity entity)
		: Moveable(position), mEntity(entity), mIntensity(intensity) {

}

Light::~Light() {

}

void Light::log() {
	FLOG_INFO("Light mIntensity: R:%f G:%f B:%f A:%f", mIntensity.x,
			mIntensity.y, mIntensity.z, mIntensity.w);
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

} /* space */
} /* fillwave */
