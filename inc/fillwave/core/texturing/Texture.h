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

#include <fillwave/common/Aliases.h>

#include <fillwave/core/texturing/Parameter.h>

#include <memory>

#ifdef __APPLE__
#include <stdlib.h>
#elif defined(_WIN32)
#include <stdlib.h>
#endif

namespace flw {
namespace flc {

//class
class Texture {
public:
  Texture(GLenum textureTarget = GL_TEXTURE_2D, GLsizei howMany = 1);

  virtual ~Texture();

  virtual void bind(GLuint id = 0);

  virtual void bind(GLint textureUnit, GLuint id = 0);

  virtual void unbind();

  void generateMipMaps();

  void setParameter(GLenum parameter, GLenum value);

  void setParameters(ParameterList paramers);

  virtual GLint getTarget();

  virtual void reload();

  virtual void log() = 0;

  GLuint getHandle(GLuint id = 0);

 protected:
  GLsizei mHowMany;
  GLuint mHandles[FILLWAVE_GLOBJECTS_MAX];
  GLenum mTarget;
};

void bindTexture(GLuint target, GLuint handle);

void bindTexture(GLint textureUnit, GLuint target, GLuint handle);

void unbindTexture(GLuint target);

} /* flc */
} /* flw */
