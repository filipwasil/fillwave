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

#include <fillwave/space/LightSpot.h>
#include <fillwave/Log.h>

FLOGINIT("Spotlight", FERROR | FFATAL)

namespace flw {
namespace flf {

LightSpot::LightSpot(flc::Texture2DRenderable* shadowTexture,
    glm::vec3 position,
    glm::quat rotation,
    glm::vec4 intensity,
    Moveable* followed)
    : Light(position
    , intensity
    , followed)
    , mShadowTexture(shadowTexture)
    , mShadowCamera(std::make_unique<CameraPerspective>(position, rotation, glm::radians(90.0f), 1.0f, 0.1f, 1000.0f)) {
  // nothing
}

LightSpot::~LightSpot() = default;

flc::Texture2DRenderable *LightSpot::getShadowTexture() {
  return mShadowTexture;
}

/*
 * getShadowCamera
 * \brief get the shadow caster camera matrix
 */

CameraPerspective *LightSpot::getShadowCamera() {
  return mShadowCamera.get();
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
  fLogI("Light mTranslation:", mTranslation.x, mTranslation.y, mTranslation.z);
  fLogI("Light mIntensity: ", mIntensity.x, " ", mIntensity.y, " ", mIntensity.z, " ", mIntensity.w);
  Light::log();
}

} /* flf */
} /* flw */
