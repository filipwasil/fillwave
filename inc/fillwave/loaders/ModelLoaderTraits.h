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

#include <fillwave/Config.h>

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <assimp/material.h>

#include <fillwave/loaders/modelLoaderTraits/ModelLoaderAssimp.h>

namespace flw {
namespace flf {
  using ModelLoaderTraits = ModelLoaderTraitsAssimp;
} /* flf */
} /* flw */

#elif defined(FILLWAVE_MODEL_LOADER_TINY_OBJ_LOADER)

#include <tinyobjloader/tiny_obj_loader.h>

#include <fillwave/loaders/modelLoaderTraits/ModelLoaderTinyObjLoader.h>

namespace flw {
namespace flf {
  using ModelLoaderTraits = ModelLoaderTraitsTinyObjLoader;
} /* flf */
} /* flw */

#else

#include <fillwave/loaders/modelLoaderTraits/ModelLoaderDefault.h>

namespace flw {
namespace flf {
  using ModelLoaderTraits = ModelLoaderTraitsDefault;
} /* flf */
} /* flw */

#endif

constexpr int FILLWAVE_DO_NOT_ANIMATE = -1;
constexpr int FILLWAVE_MAX_BONES = 45;
constexpr int FILLWAVE_MAX_TEXTS = 512;
#define FILLWAVE_MAX_BONES_DEPENDENCIES 4 // todo rewrite program factory
