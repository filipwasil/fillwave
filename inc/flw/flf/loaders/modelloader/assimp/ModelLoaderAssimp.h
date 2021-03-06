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

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <assimp/material.h>

#include <flw/flf/loaders/modelloader/assimp/AnimatorAssimp.h>

namespace flw {
namespace flf {

struct ModelLoaderTraitsAssimp {
  struct SceneType {
    SceneType (const std::string& filename);
    Assimp::Importer mImporter;
    const aiScene* mScene;
  };

  using NodeType = aiNode;
  using ShapeType = aiMesh;
  using MaterialType = aiMaterial;
  using TextureType = aiTextureType;
  using String = aiString;
  using Animator = AnimatorAssimp;

  static constexpr int COUNT_BONES_DEFINED = 45;
  static constexpr int COUNT_BONES_USED = 4;
  static constexpr int FLAG_ANIMATION_OFF = -1;
};

} /* flf */
} /* flw */
