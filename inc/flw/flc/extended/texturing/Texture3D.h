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
#include <flw/flc/texturing/Texture.h>
#include <flw/flf/loaders/textureloader/TextureConfigs.h>

namespace flw {
namespace flc {

/*! \class Texture3D
 * \brief Single GLSL 3D Texture object.
 * It consists of six 2D images.
 */

class Texture3D final {
private:
  void sendData(TextureConfig* file, GLubyte* customData = nullptr);

public:
  Texture mTexture;

  pu<TextureConfig> mRight; /* Positive X*/
  pu<TextureConfig> mLeft; /* Negative X*/
  pu<TextureConfig> mCeil; /* Positive Y*/
  pu<TextureConfig> mFloor; /* Negative Y*/
  pu<TextureConfig> mFront; /* Positive Z*/
  pu<TextureConfig> mBack; /* Negative Z*/

  ParameterList mParameters;

  Texture3D(
    TextureConfig* right
    , TextureConfig* left
    , TextureConfig* ceil
    , TextureConfig* floor
    , TextureConfig* front
    , TextureConfig* back
    , ParameterList& param);

  ~Texture3D() = default;

  void sendData();

  void bind(GLuint idx = 0);

  void bind(GLint textureUnit, GLuint idx = 0);

  void unbind();

  void setParameter(GLenum parameter, GLenum value);

  void setParameters(ParameterList parameters);

  void log();

  void reload();

  static void unbindCubemapTexture(GLint textureUnit);

  static void unbindCubemapTextures();

  void sendData(GLubyte* xp, GLubyte* xn, GLubyte* yp, GLubyte* yn, GLubyte* zp, GLubyte* zn);
};

} /* flc */
} /* flw */
