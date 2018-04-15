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

#include <fillwave/loaders/modelloader/tinyobjloader/ModelLoaderTinyObjLoader.h>
#include <fillwave/loaders/FileLoader.h>
#include <tinyobjloader/tiny_obj_loader.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

ModelLoaderTraitsTinyObjLoader::Scene::Scene(const std::string& filename) {
  std::string err = tinyobj::LoadObj(mShapes, mMaterials, filename.c_str());
  if (!err.empty()) {
    fLogE(err);
  }
}

template<>
void TModelLoader<ModelLoaderTraitsTinyObjLoader>::getPhysicsBuffer(const char*, PhysicsMeshBuffer& /*buffer*/) {
  // nothing
}

template<>
std::vector<TModelLoader<ModelLoaderTraitsTinyObjLoader>::Node*> TModelLoader<ModelLoaderTraitsTinyObjLoader>::getChildren(const Node* /*node*/) {
  std::vector<Node*> children;
  return children;
}

template<>
TModelLoader<ModelLoaderTraitsTinyObjLoader>::Node* TModelLoader<ModelLoaderTraitsTinyObjLoader>::getRootNode(const Scene&) {
  return static_cast<Node*>(nullptr);
}

template<>
TModelLoader<ModelLoaderTraitsTinyObjLoader>::Animator* TModelLoader<ModelLoaderTraitsTinyObjLoader>::getAnimator(const Scene&) {
  return static_cast<Animator*>(nullptr);
}

template<>
const Material TModelLoader<ModelLoaderTraitsTinyObjLoader>::getMaterial(const MaterialType& material) {
  Material mat;
  mat.mAmbient = glm::vec4(material.ambient[0], material.ambient[1], material.ambient[2], 1.0);
  mat.mDiffuse = glm::vec4(material.diffuse[0], material.diffuse[1], material.diffuse[2], 1.0);
  mat.mSpecular = glm::vec4(material.specular[0], material.specular[1], material.specular[2], 1.0);
  return mat;
}

template<>
flw::flc::VertexBufferBasic*
TModelLoader<ModelLoaderTraitsTinyObjLoader>::getVertexBuffer(
  const ShapeType* shape
  , Animator* /*a*/) {
  vec<flw::flc::VertexBasic> vertices;

  vertices.resize(shape->mesh.normals.size());

  const auto sizeN = shape->mesh.normals.size();
  for (size_t f = 0; f < sizeN; f+=3) {
    vertices[f].mNormal[0] = shape->mesh.normals[f];
    vertices[f + 1].mNormal[1] = shape->mesh.normals[f + 1];
    vertices[f + 2].mNormal[2] = shape->mesh.normals[f + 2];
  }

  const auto sizeP = shape->mesh.positions.size();
  for (size_t f = 0; f < sizeP; f+=3) {
    vertices[f].mPosition[0] = shape->mesh.positions[f];
    vertices[f + 1].mPosition[1] = shape->mesh.positions[f + 1];
    vertices[f + 2].mPosition[2] = shape->mesh.positions[f + 2];
  }

  const auto sizeUV = shape->mesh.texcoords.size();
  for (size_t f = 0; f < sizeUV; f+=2) {
    vertices[f].mTextureUV[0] = shape->mesh.texcoords[f];
    vertices[f + 1].mTextureUV[1] = shape->mesh.texcoords[f + 1];
  }

  return new flc::VertexBufferBasic(vertices);
}

template<>
flc::IndexBuffer* TModelLoader<ModelLoaderTraitsTinyObjLoader>::getIndexBuffer(const ShapeType* shape) {
  std::vector<GLuint> indices;
  indices.resize(shape->mesh.indices.size());
  for (size_t f = 0; f < shape->mesh.indices.size(); ++f) {
    indices[f] = shape->mesh.indices[f];
  }
  return new ::flw::flc::IndexBuffer(indices);
}

template<>
void TModelLoader<ModelLoaderTraitsTinyObjLoader>::setTransformation(const Node* /*node*/, Entity* /*entity*/) {
 // todo
}

template<>
std::vector<TModelLoader<ModelLoaderTraitsTinyObjLoader>::MeshCreationInfo>
TModelLoader<ModelLoaderTraitsTinyObjLoader>::getMeshes(const Node* /*node*/, const Scene& scene) {
  std::vector<TModelLoader<ModelLoaderTraitsTinyObjLoader>::MeshCreationInfo> meshes;
  meshes.reserve(scene.mShapes.size());

  for (auto& shape : scene.mShapes) {
    if (shape.mesh.material_ids.empty()) {
      TModelLoader<ModelLoaderTraitsTinyObjLoader>::MeshCreationInfo mesh = {
        &shape
        , Material()
        , ""
        , ""
        , ""
      };
      meshes.push_back(mesh);
    } else {
      const auto materialID = shape.mesh.material_ids[0];
      TModelLoader<ModelLoaderTraitsTinyObjLoader>::MeshCreationInfo mesh = {
        &shape
        , getMaterial(scene.mMaterials[materialID])
        , scene.mMaterials[materialID].diffuse_texname
        , scene.mMaterials[materialID].bump_texname
        , scene.mMaterials[materialID].specular_texname
      };
      meshes.push_back(mesh);
    }
  }

  return meshes;
}

template
class TModelLoader<ModelLoaderTraitsTinyObjLoader>;

} /* flf */
} /* flw */
