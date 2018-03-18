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

#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/core/buffers/IndexBuffer.h>

#include <fillwave/models/shapes/PhysicsMeshBuffer.h>
#include <fillwave/models/base/Material.h>

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

template<>
flw::flc::VertexBufferBasic*
TModelLoader<ModelLoaderTraitsTinyObjLoader>::getVertexBuffer(const ShapeType* shape, const ShapeDataType* d, Animator* a) {
  flw::flc::VertexBufferBasic* vertices;

//  VertexBufferBasic::VertexBufferBasic(const tinyobj::shape_t& shape,
//  const tinyobj::attrib_t& attr,
//  GLuint dataStoreModification) :
//  TVertexBuffer<VertexBasic>(dataStoreModification) {

  mTotalElements = shape.mesh.indices.size();
  mDataVertices.resize(mTotalElements);

  // Loop over shapes
  // Loop over faces(polygon)
  size_t index_offset = 0;
  /* xxx OpenMP should be usefull here */
  for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
    int fv = shape.mesh.num_face_vertices[f];

    // Loop over vertices in the face.
    for (size_t v = 0; v < fv; v++) {
      // access to vertex
      size_t idxOut = index_offset + v;
      tinyobj::index_t idx = shape.mesh.indices[idxOut];
      mDataVertices[idxOut].mPosition[0] = attr.vertices[3 * idx.vertex_index + 0];
      mDataVertices[idxOut].mPosition[1] = attr.vertices[3 * idx.vertex_index + 1];
      mDataVertices[idxOut].mPosition[2] = attr.vertices[3 * idx.vertex_index + 2];
      mDataVertices[idxOut].mPosition[3] = 1.0f;
      mDataVertices[idxOut].mNormal[0] = attr.normals[3 * idx.normal_index + 0];
      mDataVertices[idxOut].mNormal[1] = attr.normals[3 * idx.normal_index + 1];
      mDataVertices[idxOut].mNormal[2] = attr.normals[3 * idx.normal_index + 2];
      mDataVertices[idxOut].mTextureUV[0] = attr.texcoords[2 * idx.texcoord_index +
                                                           0];
      mDataVertices[idxOut].mTextureUV[1] = attr.texcoords[2 * idx.texcoord_index +
                                                           1];
      mDataVertices[idxOut].mNormalTangentMap[0] = 0.0f;
      mDataVertices[idxOut].mNormalTangentMap[1] = 0.0f;
      mDataVertices[idxOut].mNormalTangentMap[2] = 0.0f;
      mDataVertices[idxOut].mColor[0] = 0.0f;
      mDataVertices[idxOut].mColor[1] = 0.0f;
      mDataVertices[idxOut].mColor[2] = 0.0f;
      mDataVertices[idxOut].mColor[3] = 1.0f;
      for (int k = 0; k < FILLWAVE_MAX_BONES_DEPENDENCIES; k++) {
        mDataVertices[idxOut].mBoneID[k] = 0.0f;
        mDataVertices[idxOut].mBoneWeight[k] = 0.0f;
      }
    }
    index_offset += fv;

    /* per-face material */
    /* shape.mesh.material_ids[f]; */
  }
  mData = mDataVertices.data();
  mSize = mTotalElements * sizeof(VertexBasic);
}

template<>
flc::IndexBuffer* TModelLoader<ModelLoaderTraitsTinyObjLoader>::getIndexBuffer(const ShapeType* shape) {

  std::vector<GLuint> indices;

  return new ::flw::flc::IndexBuffer(indices);
}

template
class TModelLoader<ModelLoaderTraitsTinyObjLoader>;

} /* flf */
} /* flw */
