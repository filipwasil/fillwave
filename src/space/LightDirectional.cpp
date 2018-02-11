/*
 * LightDirectional.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
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


#include <fillwave/space/LightDirectional.h>
#include <fillwave/Log.h>

FLOGINIT("DirectionalLight", FERROR | FFATAL)

namespace flw {
namespace flf {

LightDirectional::LightDirectional(
  flc::Texture2DRenderable* tex,
  glm::vec3 pos,
  glm::quat rot,
  glm::vec4 intensity,
  Moveable* observed)
  : Light(pos, intensity, observed)
  , mShadowTexture(tex)
  , mShadowCamera(std::make_unique<CameraOrthographic>(pos, rot, -10.0f, 10.0f, 10.0f, -10.0f, 0.1f, 1000.0f)) {
  //  nothing
}

LightDirectional::~LightDirectional() = default;

CameraOrthographic* LightDirectional::getShadowCamera() {
  return mShadowCamera.get();
}

flc::Texture2DRenderable* LightDirectional::getShadowTexture() {
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

void LightDirectional::log() {
  const auto translation = mShadowCamera->getTranslation();
  const auto eyeMatrix = mShadowCamera->getEye();
  fLogI("mShadowCamera->getTranslation(): ", translation.x, translation.y, translation.z);
  fLogI("mShadowCamera[0]: ", eyeMatrix[0].x, " ", eyeMatrix[0].y, " ", eyeMatrix[0].z, " ", eyeMatrix[0].w);
  fLogI("mShadowCamera[1]: ", eyeMatrix[1].x, " ", eyeMatrix[1].y, " ", eyeMatrix[1].z, " ", eyeMatrix[1].w);
  fLogI("mShadowCamera[2]: ", eyeMatrix[2].x, " ", eyeMatrix[2].y, " ", eyeMatrix[2].z, " ", eyeMatrix[2].w);
  fLogI("mShadowCamera[3]: ", eyeMatrix[3].x, " ", eyeMatrix[3].y, " ", eyeMatrix[3].z, " ", eyeMatrix[3].w);
  fLogI("Light mIntensity: R:", mIntensity.x, "G: ", mIntensity.y, "B: ",mIntensity.z, "A: ", mIntensity.w);
}

} /* flf */
} /* flw */
