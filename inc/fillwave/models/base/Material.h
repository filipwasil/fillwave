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

#include <fillwave/Math.h>
#include <fillwave/loaders/ModelLoaderTraits.h>

namespace flw {
namespace flf {

/*! \class Material
 * \brief Per mesh material info.
 */

class Material final {
public:
  Material();

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  Material(const aiMaterial* material);

#else
  Material(const tinyobj::material_t& material);
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

  const glm::vec4 &getAmbient() const;

  const glm::vec4 &getDiffuse() const;

  const glm::vec4 &getSpecular() const;

private:
  glm::vec4 mAmbient;
  glm::vec4 mDiffuse;
  glm::vec4 mSpecular;
};

} /* flf */
} /* flw */
