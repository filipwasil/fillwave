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

#include <fillwave/models/animations/Animator.h>

#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/core/buffers/IndexBuffer.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

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

  Importer importer;

  auto scene = importer.ReadFile(assetPath, aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_CalcTangentSpace);

  if (nullptr == scene) {
    return;
  }

  if (1 != scene->mNumMeshes) {
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

template<>
const TModelLoader<ModelLoaderTraitsAssimp>::Scene* TModelLoader<ModelLoaderTraitsAssimp>::getScene(const char* path) {
  return mImporter->ReadFile(path, mFlags);
}

template<>
Material TModelLoader<ModelLoaderTraitsAssimp>::getMaterial(const MaterialType& mat) {
  Material material;
  aiColor4D color;
  if (AI_SUCCESS == aiGetMaterialColor(&mat, AI_MATKEY_COLOR_AMBIENT, &color)) {
    material.mAmbient = glm::vec4(color.r, color.b, color.g, color.a);
  }
  if (AI_SUCCESS == aiGetMaterialColor(&mat, AI_MATKEY_COLOR_DIFFUSE, &color)) {
    material.mDiffuse = glm::vec4(color.r, color.b, color.g, color.a);
  }
  if (AI_SUCCESS == aiGetMaterialColor(&mat, AI_MATKEY_COLOR_SPECULAR, &color)) {
    material.mSpecular = glm::vec4(color.r, color.b, color.g, color.a);
  }
  return material;
}

template<>
flc::IndexBuffer* TModelLoader<ModelLoaderTraitsAssimp>::getIndexBuffer(const ShapeType* shape) {

  std::vector<GLuint> indices;

  indices.resize(shape->mNumFaces * 3);

  #pragma omp parallel for schedule(guided) num_threads(2) if (shape->mNumFaces > 1000)
    for (GLuint i = 0; i < shape->mNumFaces; i++) {
      const GLuint idx = 3 * i;
      indices[idx] = shape->mFaces[i].mIndices[0];
      indices[idx + 1] = shape->mFaces[i].mIndices[1];
      indices[idx + 2] = shape->mFaces[i].mIndices[2];
    }

  return new ::flw::flc::IndexBuffer(indices);
}

template<>
flw::flc::VertexBufferBasic*
  TModelLoader<ModelLoaderTraitsAssimp>::getVertexBuffer(const ShapeType* shape, const ShapeDataType* /*d*/, Animator* a) {
  std::vector<flc::VertexBasic> vertices;

  const size_t elements = shape->mNumVertices;

  vertices.resize(elements);

  {
#pragma omp parallel for schedule(guided) num_threads(2) if (shape->mNumVertices > 1000)
    for (GLuint i = 0; i < elements; i++) {
      flc::VertexBasic &vertex = vertices[i];

      if (shape->HasVertexColors(0)) {
        vertex.mColor[0] = shape->mColors[0]->r;
        vertex.mColor[1] = shape->mColors[0]->g;
        vertex.mColor[2] = shape->mColors[0]->b;
        vertex.mColor[3] = shape->mColors[0]->a;
      } else {
        vertex.mColor[0] = 0.0f;
        vertex.mColor[1] = 0.0f;
        vertex.mColor[2] = 0.0f;
        vertex.mColor[3] = 1.0f;
      }

      vertex.mPosition[0] = shape->mVertices[i].x;
      vertex.mPosition[1] = shape->mVertices[i].y;
      vertex.mPosition[2] = shape->mVertices[i].z;
      vertex.mPosition[3] = 1.0f;

      /* One normal each triangle - on */
      if (shape->HasNormals()) {
        vertex.mNormal[0] = shape->mNormals[i].x;
        vertex.mNormal[1] = shape->mNormals[i].y;
        vertex.mNormal[2] = shape->mNormals[i].z;
      } else {
        vertex.mNormal[0] = 0;
        vertex.mNormal[1] = 0;
        vertex.mNormal[2] = 0;
      }

      if (shape->HasTextureCoords(0)) {
        vertex.mTextureUV[0] = shape->mTextureCoords[0][i].x;
        vertex.mTextureUV[1] = shape->mTextureCoords[0][i].y;
      } else {
        vertex.mTextureUV[0] = 0;
        vertex.mTextureUV[1] = 0;
      }

      if (shape->HasTangentsAndBitangents()) {
        vertex.mNormalTangentMap[0] = shape->mTangents[i].x;
        vertex.mNormalTangentMap[1] = shape->mTangents[i].y;
        vertex.mNormalTangentMap[2] = shape->mTangents[i].z;
      } else {
        vertex.mNormalTangentMap[0] = 0;
        vertex.mNormalTangentMap[1] = 0;
        vertex.mNormalTangentMap[2] = 0;
      }
      for (int k = 0; k < FILLWAVE_MAX_BONES_DEPENDENCIES; k++) {
        vertex.mBoneID[k] = 0;
        vertex.mBoneWeight[k] = 0.0f;
      }
    }
  }

  if (a) {
    std::vector<int> boneIdForEachVertex;
    boneIdForEachVertex.resize(vertices.size());
    for (size_t z = 0; z < vertices.size(); z++) {
      boneIdForEachVertex[z] = 0;
    }
    /* Bones */
    for (GLuint i = 0; i < shape->mNumBones; i++) {
      for (GLuint j = 0; j < shape->mBones[i]->mNumWeights; j++) {
        GLuint VertexID = shape->mBones[i]->mWeights[j].mVertexId;
        float Weight = shape->mBones[i]->mWeights[j].mWeight;
        if (boneIdForEachVertex[VertexID] < FILLWAVE_MAX_BONES_DEPENDENCIES) {
          vertices[VertexID].mBoneID[boneIdForEachVertex[VertexID]] = a->getBoneId(shape->mBones[i]->mName.C_Str());
          vertices[VertexID].mBoneWeight[boneIdForEachVertex[VertexID]] = Weight;
          boneIdForEachVertex[VertexID]++;
        } else {
          fLogF("Crater can handle maximum %d bone dependencies.", FILLWAVE_MAX_BONES_DEPENDENCIES);
        }
      }
    }
  }
  return new flc::VertexBufferBasic (vertices);
}

template<>
void TModelLoader<ModelLoaderTraitsAssimp>::assignTransformation (const Node* node, Entity* entity) {
  aiVector3t<float> scale;
  aiQuaterniont<float> rot;
  aiVector3t<float> pos;
  node->mTransformation.Decompose(scale, rot, pos);
  entity->scaleTo(glm::vec3(scale.x, scale.y, scale.z));
  entity->rotateTo(glm::quat(rot.w, rot.x, rot.y, rot.z));
  entity->moveTo(glm::vec3(pos.x, pos.y, pos.z));
}

template
class TModelLoader<ModelLoaderTraitsAssimp>;

} /* flf */
} /* flw */
