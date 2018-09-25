/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/flf/space/base/Light.h>
#include <flw/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

Light::Light(glm::vec3 pos, glm::vec4 intensity, Moveable* observed)
    : Moveable(pos)
    , mObserved(observed)
    , mIsFollowedUpdated(true)
    , mIntensity(intensity) {
  if (nullptr != mObserved) {
    mObserved->addObserver(this);
  }
}

Light::~Light() {
  if (nullptr != mObserved) {
    mObserved->dropObserver(this);
  }
}

void Light::updateFromFollowed() {
  if (mObserved && mIsFollowedUpdated) {
    mTranslation = glm::vec3(mObserved->getParentMMC() * glm::vec4(mObserved->getTranslation(), 1.0));
    mRotation = glm::normalize(mObserved->getParentRotation() * mObserved->getRotation());
    mRefresh = true;
    mIsFollowedUpdated = false;
  }
}

void Light::setAttenuation(LightAttenuationData &attenuation) {
  mAttenuation = attenuation;
}

LightAttenuationData Light::getAttenuation() {
  return mAttenuation;
}

void Light::setIntensity(glm::vec4 intensity) {
  mIntensity = intensity;
  mRefresh = true;
}

glm::vec4 Light::getIntensity() {
  return mIntensity;
}

void Light::log() {
  fLogI("Light mTranslation:", mTranslation.x, mTranslation.y, mTranslation.z);
}

void Light::onDestroy(Observable* observable) {
  if (mObserved == observable) {
    mObserved = nullptr;
  }
}

void Light::onChanged(Observable* /*observable*/) {
  mIsFollowedUpdated = true;
}
} /* flf */
} /* flw */
