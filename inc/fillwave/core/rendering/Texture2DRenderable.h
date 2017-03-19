/*
 * Texture2DRenderable.h
 *
 *  Created on: Aug 13, 2014
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TEXTURE2DRENDERABLE_H_
#define TEXTURE2DRENDERABLE_H_

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/rendering/Framebuffer.h>

namespace fillwave {
namespace core {

/*! \class Texture2DRenderable
 * \brief One can render to this texture and use the rendered image as a 2D texture.
 */

class Texture2DRenderable : public Texture2D {
public:
  Texture2DRenderable(GLenum attachment, Texture2DFile *file, ParameterList &parameters);

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

private:
  puFramebuffer mFramebuffer;
  GLenum mAttachment;
};

} /* core */
typedef std::shared_ptr<core::Texture2DRenderable> pTexture2DRenderable;
typedef std::unique_ptr<core::Texture2DRenderable> puTexture2DRenderable;
} /* fillwave */
#endif /* TEXTURE2DRENDERABLE_H_ */
