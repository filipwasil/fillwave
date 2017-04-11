/*
 * Material.cpp
 *
 *  Created on: 27 sty 2015
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


#include <fillwave/models/base/Material.h>
#include <fillwave/models/animations/Conversion.h>

namespace flw {
namespace flf {

Material::Material()
    : mAmbient(0.1, 0.1, 0.1, 1.0), mDiffuse(1.0), mSpecular(1.0) {
}

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

Material::Material(const aiMaterial *material) {
  aiColor4D color;
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color)) {
    mAmbient = assimpToGlmVec4(color);
  }
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color)) {
    mDiffuse = assimpToGlmVec4(color);
  }
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color)) {
    mSpecular = assimpToGlmVec4(color);
  }
}

#else
Material::Material(const tinyobj::material_t& material) :
  mAmbient (floatsToGlmVec4(material.ambient)),
  mDiffuse (floatsToGlmVec4(material.diffuse)),
  mSpecular (floatsToGlmVec4(material.specular)) {
}
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

const glm::vec4 &Material::getAmbient() const {
  return mAmbient;
}

const glm::vec4 &Material::getDiffuse() const {
  return mDiffuse;
}

const glm::vec4 &Material::getSpecular() const {
  return mSpecular;
}

} /* flf */
} /* flw */
