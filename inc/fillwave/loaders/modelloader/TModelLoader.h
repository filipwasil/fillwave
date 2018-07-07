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
#include <fillwave/common/Nothing.h>
#include <fillwave/loaders/modelloader/AnimatorDefault.h>

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
  template <typename C>
  static typename C::NodeType getNodeType(bool);
  template <typename C>
  static Nothing getNodeType(...);

  using NodeType = decltype(getNodeType<Traits>(0));

  template <typename C>
  static typename C::SceneType getSceneType(bool);
  template <typename C>
  static Nothing getSceneType(...);

  using SceneType = decltype(getSceneType<Traits>(0));

  template <typename C>
  static typename C::ShapeType getShapeType(bool);
  template <typename C>
  static Nothing getShapeType(...);

  using ShapeType = decltype(getShapeType<Traits>(0));

  template <typename C>
  static typename C::MaterialType getMaterialType(bool);
  template <typename C>
  static Nothing getMaterialType(...);

  using MaterialType = decltype(getMaterialType<Traits>(0));

  template <typename C>
  static typename C::TextureType getTextureType(bool);
  template <typename C>
  static Nothing getTextureType(...);

  using TextureType = decltype(getTextureType<Traits>(0));

  template <typename C>
  static typename C::String getString(bool);
  template <typename C>
  static Nothing getString(...);

  using String = decltype(getString<Traits>(0));

  template <typename C>
  static typename C::Animator getAnimator(bool);
  template <typename C>
  static AnimatorDefault getAnimator(...);

  using Animator = decltype(getAnimator<Traits>(0));

  struct MeshCreationInfo {
    const ShapeType* shape;
    const Material material;
    const std::string diffuse;
    const std::string normal;
    const std::string specular;
  };

  static constexpr int COUNT_BONES_DEFINED = Traits::COUNT_BONES_DEFINED;
  static constexpr int COUNT_BONES_USED = Traits::COUNT_BONES_USED;
  static constexpr int FLAG_ANIMATION_OFF = Traits::FLAG_ANIMATION_OFF;

  static void getPhysicsBuffer(const char*, PhysicsMeshBuffer& buffer);
  static const Material getMaterial(const MaterialType& material);
  static ::flw::flc::IndexBuffer* getIndexBuffer(const ShapeType* shape);
  static ::flw::flc::VertexBufferBasic* getVertexBuffer(const ShapeType *shape, Animator *a);
  static void setTransformation (const NodeType* node, Entity* entity);
  static std::vector<MeshCreationInfo> getMeshes(const NodeType* node, const SceneType& scene);
  static std::vector<NodeType*> getChildren(const NodeType*);
  static NodeType* getRootNode(const SceneType&);
  static Animator* getAnimator(const SceneType&);
};

} /* flf */
} /* flw */