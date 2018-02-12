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

#include <fillwave/models/base/Material.h>
#include <fillwave/models/animations/Conversion.h>

namespace flw {
namespace flf {

Material::Material()
    : mAmbient(0.1, 0.1, 0.1, 1.0)
    , mDiffuse(1.0)
    , mSpecular(1.0) {
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
