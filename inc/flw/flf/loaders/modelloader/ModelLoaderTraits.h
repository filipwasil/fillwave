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

#include <flw/Config.h>

#if defined (FILLWAVE_MODEL_LOADER_ASSIMP)

#include <flw/flf/loaders/modelloader/assimp/ModelLoaderAssimp.h>

namespace flw {
namespace flf {
  using ModelLoaderTraits = ModelLoaderTraitsAssimp;
} /* flf */
} /* flw */

#elif defined(FILLWAVE_MODEL_LOADER_TINYOBJLOADER)

#include <flw/flf/loaders/modelloader/tinyobjloader/ModelLoaderTinyObjLoader.h>

namespace flw {
namespace flf {
  using ModelLoaderTraits = ModelLoaderTraitsTinyObjLoader;
} /* flf */
} /* flw */

#else

#include <flw/flf/loaders/modelloader/ModelLoaderDefault.h>

namespace flw {
namespace flf {
  using ModelLoaderTraits = ModelLoaderTraitsDefault;
} /* flf */
} /* flw */

#endif
