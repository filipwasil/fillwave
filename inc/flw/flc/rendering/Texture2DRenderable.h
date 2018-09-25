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

#include <flw/flc/texturing/Texture2D.h>
#include <flw/flc/rendering/Framebuffer.h>

namespace flw {
namespace flc {

/*! \class Texture2DRenderable
 * \brief One can render to this texture and use the rendered image as a 2D texture.
 */

class Texture2DRenderable  {
public:
  Texture2DRenderable(GLenum attachment, flc::TextureConfig *file, ParameterList &parameters);

  virtual ~Texture2DRenderable() = default;

  void resize(GLint width, GLint height);

  void bindForWriting();

  void bindForRendering();

  void bindForReading();

  void setAttachment(GLenum attachment, GLenum target = GL_TEXTURE_2D);

  void attachTexture2DDraw(GLenum attachment, GLenum target, GLuint texHandle);

  void attachTexture2D(GLenum attachment, GLenum target, GLuint textureHandle);

  void copyTo(Framebuffer *source);

  void copyFrom(Framebuffer *source);

  virtual void reload();

  void log();

  Texture2D mTexture2D;
 private:
  flc::Framebuffer mFramebuffer;
  GLenum mAttachment;
};

} /* flc */
} /* flw */
