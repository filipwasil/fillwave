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
