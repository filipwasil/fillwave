#pragma once

/*
* Copyright (c) 2017, Fillwave developers
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

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/rendering/Framebuffer.h>

namespace flw {
namespace flc {

/*! \class Texture2DRenderable
 * \brief One can render to this texture and use the rendered image as a 2D texture.
 */

class Texture2DRenderable : public Texture2D {
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

private:
  flc::Framebuffer mFramebuffer;
  GLenum mAttachment;
};

} /* flc */
} /* flw */
