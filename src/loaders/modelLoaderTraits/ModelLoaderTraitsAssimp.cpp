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
#include <fillwave/loaders/modelLoaderTraits/ModelLoaderAssimp.h>

namespace flw {
namespace flf {

template<>
TModelLoader<ModelLoaderTraitsAssimp>::TModelLoader()
 : mImporter(new Assimp::Importer())
 , mFlags(aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_CalcTangentSpace) {
  // nothing
}

template<>
TModelLoader<ModelLoaderTraitsAssimp>::~TModelLoader() {
  delete mImporter;
}

template<>
void TModelLoader<ModelLoaderTraitsAssimp>::getPhysicsBuffer(const char* assetPath, flf::PhysicsMeshBuffer& buffer) {

  auto scene = mImporter->ReadFile(assetPath, mFlags);

  if (nullptr == scene) {
    return;
  }

  if (scene->mNumMeshes != 1) {
    return;
  }

  const aiMesh* shape = scene->mMeshes[0];
  buffer.mNumFaces = shape->mNumFaces;
  buffer.mVertices.reserve(shape->mNumVertices);
  buffer.mIndices.reserve(shape->mNumFaces*  3);
  for (GLuint j = 0; j < shape->mNumFaces; ++j) {
    buffer.mIndices.push_back(shape->mFaces[j].mIndices[0]);
    buffer.mIndices.push_back(shape->mFaces[j].mIndices[1]);
    buffer.mIndices.push_back(shape->mFaces[j].mIndices[2]);
  }
  for (GLuint z = 0; z < shape->mNumVertices; ++z) {
    const auto& v = shape->mVertices[z];
    buffer.mVertices[z] = { { v.x, v.y, v.z } };
  }
}

template
class TModelLoader<ModelLoaderTraitsAssimp>;

} /* flf */
} /* flw */
