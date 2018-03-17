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

#include <fillwave/loaders/TModelLoader.h>
#include <fillwave/loaders/modelLoaderTraits/ModelLoaderTinyObjLoader.h>

namespace flw {
namespace flf {

template<>
TModelLoader<ModelLoaderTraitsTinyObjLoader>::TModelLoader() {
  // nothing
}

template<>
TModelLoader<ModelLoaderTraitsTinyObjLoader>::~TModelLoader() {
  // nothing
}

template<>
void TModelLoader<ModelLoaderTraitsTinyObjLoader>::getPhysicsBuffer(const char*, PhysicsMeshBuffer& buffer) {
  // nothing
}

template<>
Meterial TModelLoader<ModelLoaderTraitsTinyObjLoader>::getMaterial(const MaterialType& material) {
  Meterial mat;
  mat.mAmbient = floatsToGlmVec4(material.ambient);
  mat.mDiffuse = floatsToGlmVec4(material.diffuse);
  mat.mSpecular = floatsToGlmVec4(material.specular);
  return mat;
}

template
class TModelLoader<ModelLoaderTraitsTinyObjLoader>;

} /* flf */
} /* flw */
