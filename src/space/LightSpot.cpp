/*
 * LightSpot.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: filip
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


#include <fillwave/space/LightSpot.h>
#include <fillwave/Log.h>

FLOGINIT("Spotlight", FERROR | FFATAL)

namespace fillwave {
namespace framework {

LightSpot::LightSpot(core::Texture2DRenderable *shadowTexture,
    glm::vec3 position,
    glm::quat rotation,
    glm::vec4 intensity,
    Moveable *followed)
    : Light (position, intensity, followed), mShadowTexture (shadowTexture)
    , mShadowCamera (std::make_unique<CameraPerspective> (position, rotation, glm::radians (90.0f), 1.0f, //xxx fix
                                                          0.1f, 1000.0f)) {
}

core::Texture2DRenderable *LightSpot::getShadowTexture() {
  return mShadowTexture;
}

/*
 * getShadowCamera
 * \brief get the shadow caster camera matrix
 */

CameraPerspective *LightSpot::getShadowCamera() {
  return mShadowCamera.get ();
}

void LightSpot::updateShadowCamera() {
  if (mShadowCamera->getTranslation () != mTranslation) {
    mShadowCamera->moveTo (mTranslation);
    mShadowCamera->update ();
  }
  if (mShadowCamera->getRotation () != mRotation) {
    mShadowCamera->rotateTo (mRotation);
    mShadowCamera->update ();
  }
}

void LightSpot::log() {
  auto d = [](GLfloat f) {
    return static_cast<double>(f);
  };
  fLogI("mShadowCamera->getTranslation(): :%f :%f :%f",
        d (mShadowCamera->getTranslation ().x),
        d (mShadowCamera->getTranslation ().y),
        d (mShadowCamera->getTranslation ().z));
  fLogI("mShadowCamera[0]: :%f :%f :%f :%f",
        d (mShadowCamera->getEye ()[0].x),
        d (mShadowCamera->getEye ()[0].y),
        d (mShadowCamera->getEye ()[0].z),
        d (mShadowCamera->getEye ()[0].w));
  fLogI("mShadowCamera[1]: :%f :%f :%f :%f",
        d (mShadowCamera->getEye ()[1].x),
        d (mShadowCamera->getEye ()[1].y),
        d (mShadowCamera->getEye ()[1].z),
        d (mShadowCamera->getEye ()[1].w));
  fLogI("mShadowCamera[2]: :%f :%f :%f :%f",
        d (mShadowCamera->getEye ()[2].x),
        d (mShadowCamera->getEye ()[2].y),
        d (mShadowCamera->getEye ()[2].z),
        d (mShadowCamera->getEye ()[2].w));
  fLogI("mShadowCamera[3]: :%f :%f :%f :%f",
        d (mShadowCamera->getEye ()[3].x),
        d (mShadowCamera->getEye ()[3].y),
        d (mShadowCamera->getEye ()[3].z),
        d (mShadowCamera->getEye ()[3].w));
  fLogI("Light mTranslation: X:%f Y:%f Z:%f", d (mTranslation.x), d (mTranslation.y), d (mTranslation.z));
  fLogI("Light mIntensity: R:%f G:%f B:%f A:%f",
        d (mIntensity.x),
        d (mIntensity.y),
        d (mIntensity.z),
        d (mIntensity.w));
  Light::log ();
}

} /* framework */
} /* fillwave */
