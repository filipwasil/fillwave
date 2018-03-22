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

#include <fillwave/common/Nothing.h>
#include <fillwave/models/animations/AnimatorDefault.h>

#include <tinyobjloader/tiny_obj_loader.h>

namespace flw {
namespace flf {

struct ModelLoaderTraitsTinyObjLoader {

  using Node = Nothing;
  using Scene = Nothing;
  using ShapeType = tinyobj::shape_t;
  using ShapeDataType = tinyobj::attrib_t;
  using MaterialType = tinyobj::material_t;
  using TextureType = Nothing;
  using String = Nothing;
  using Importer = Nothing;
  using Animator = AnimatorDefault;
  using Flags = Nothing;

  static constexpr int COUNT_BONES_DEFINED = 1;
  static constexpr int COUNT_BONES_USED = 1;
  static constexpr int FLAG_ANIMATION_OFF = -1;
};

} /* flf */
} /* flw */
