/*
 * Light.cpp
 *
 *  Created on: 17 Apr 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <fillwave/space/base/Light.h>
#include <fillwave/Log.h>

FLOGINIT("Light", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Light::Light(glm::vec3 position, glm::vec4 intensity, Moveable* followed) :
	Moveable(position), mFollowed(followed), mIsFollowedUpdated(true),
	mIntensity(intensity) {
	if (nullptr != mFollowed) {
		mFollowed->addObserver(this);
	}
}

Light::~Light() {
	if (nullptr != mFollowed) {
		mFollowed->dropObserver(this);
	}
}

void Light::updateFromFollowed() {
	if (mFollowed && mIsFollowedUpdated) {
		mTranslation = glm::vec3(
		                  mFollowed->getParentMMC()
		                  * glm::vec4(mFollowed->getTranslation(), 1.0));
		mRotation = glm::normalize(
		               mFollowed->getParentRotation() * mFollowed->getRotation());
		mRefresh = GL_TRUE;
		mIsFollowedUpdated = false;
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
	auto d = [] (GLfloat & f) {
		return static_cast<double>(f);
	};
	fLogI("Light mIntensity: R:%f G:%f B:%f A:%f", d(mIntensity.x),
	          d(mIntensity.y), d(mIntensity.z), d(mIntensity.w));
}

void Light::onDeath(Observable* observable) {
	if (mFollowed == observable) {
		mFollowed = nullptr;
	}
}

void Light::onChanged(Observable* /*observable*/) {
	mIsFollowedUpdated = true;
}
} /* framework */
} /* fillwave */
