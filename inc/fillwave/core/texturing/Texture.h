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

#include <fillwave/core/GLObject.h>
#include <fillwave/loaders/TextureLoader.h>
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
class Texture : public GLObject {
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

protected:
  GLenum mTarget;
};

void bindTexture(GLuint target, GLuint handle);

void bindTexture(GLint textureUnit, GLuint target, GLuint handle);

void unbindTexture(GLuint target);

} /* flc */
typedef std::unique_ptr<flc::Texture2DFile> puTexture2DFile;
} /* flw */
