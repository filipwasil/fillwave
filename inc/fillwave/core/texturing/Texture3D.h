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
#include <fillwave/loaders/TextureConfigs.h>

namespace flw {
namespace flc {

/*! \class Texture3D
 * \brief Single GLSL 3D Texture object.
 * It consists of six 2D images.
 */

class Texture3D : public Texture {
private:
  void sendData(TextureConfig* file, GLubyte* customData = nullptr);

public:
  pu<TextureConfig> mRight; /* Positive X*/
  pu<TextureConfig> mLeft; /* Negative X*/
  pu<TextureConfig> mCeil; /* Positive Y*/
  pu<TextureConfig> mFloor; /* Negative Y*/
  pu<TextureConfig> mFront; /* Positive Z*/
  pu<TextureConfig> mBack; /* Negative Z*/

  Texture3D(TextureConfig* right, TextureConfig* left, TextureConfig* ceil, TextureConfig* floor, TextureConfig* front, TextureConfig* back, ParameterList& param);

  virtual ~Texture3D() = default;

  void sendData();

  void log();

  static void unbindCubemapTexture(GLint textureUnit);

  static void unbindCubemapTextures();

  void sendData(GLubyte* xp, GLubyte* xn, GLubyte* yp, GLubyte* yn, GLubyte* zp, GLubyte* zn);
};

} /* flc */
} /* flw */
