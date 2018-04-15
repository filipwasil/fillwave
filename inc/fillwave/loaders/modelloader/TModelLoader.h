#pragma once

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

#include <fillwave/loaders/modelloader/ModelLoaderTraits.h>
#include <fillwave/models/base/Material.h>

namespace flw {

namespace flc {
class IndexBuffer;
class VertexBufferBasic;
}

namespace flf {

class Animator;
class Entity;
struct Material;
struct PhysicsMeshBuffer;

template <class Traits>
struct TModelLoader final {
  using Node = typename ModelLoaderTraits::Node;
  using Scene = typename ModelLoaderTraits::Scene;
  using ShapeType = typename ModelLoaderTraits::ShapeType;
  using MaterialType = typename ModelLoaderTraits::MaterialType;
  using TextureType = typename ModelLoaderTraits::TextureType;
  using String = typename ModelLoaderTraits::String;
  using Animator = typename ModelLoaderTraits::Animator;

  struct MeshCreationInfo {
    const ShapeType* shape;
    const Material material;
    const std::string diffuse;
    const std::string normal;
    const std::string specular;
  };

  static constexpr int COUNT_BONES_DEFINED = ModelLoaderTraits::COUNT_BONES_DEFINED;
  static constexpr int COUNT_BONES_USED = ModelLoaderTraits::COUNT_BONES_USED;
  static constexpr int FLAG_ANIMATION_OFF = ModelLoaderTraits::FLAG_ANIMATION_OFF;

  static void getPhysicsBuffer(const char*, PhysicsMeshBuffer& buffer);
  static const Material getMaterial(const MaterialType& material);
  static Material getTexturePath(TextureType type, const MaterialType& material);
  static ::flw::flc::IndexBuffer* getIndexBuffer(const ShapeType* shape);
  static ::flw::flc::VertexBufferBasic* getVertexBuffer(const ShapeType *shape, Animator *a);
  static void setTransformation (const Node* node, Entity* entity);
  static std::vector<MeshCreationInfo> getMeshes(const Node* node, const Scene& scene);
  static std::vector<Node*> getChildren(const Node*);
  static Node* getRootNode(const Scene&);
  static Animator* getAnimator(const Scene&);
};

} /* flf */
} /* flw */
