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

#include <fillwave/core/texturing/Texture.h>
#include <fillwave/loaders/textureloader/TextureConfigs.h>

namespace flw {
namespace flc {

struct TextureConfig;

/*! \class Texture2D
 * \brief Single GLSL 2D Texture object.
 */

class Texture2D final {
public:
  Texture2D(TextureConfig* file, ParameterList &parameters, GLuint howMany = 1);

  ~Texture2D() = default;

  void sendData(GLubyte* data = nullptr);

  void reload();

  void bind(GLuint idx = 0);

  void bind(GLint textureUnit, GLuint idx = 0);

  void unbind();

  void generateMipMaps();

  void setParameter(GLenum parameter, GLenum value);

  void setParameters(ParameterList parameters);

  void log();

  static void unbind2DTexture(GLint textureUnit);

  static void unbind2DTextures();

  Texture mTexture;
  pu<TextureConfig> mCfg;
  ParameterList mParameters;
};

} /* flc */
} /* flw */
