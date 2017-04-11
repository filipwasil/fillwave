/*
 * Texture.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 *
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

#include <fillwave/core/texturing/Texture.h>
#include <fillwave/Log.h>

FLOGINIT("Texture", FERROR | FFATAL | FDEBUG)

namespace flw {
namespace flc {

Texture::Texture(GLenum textureTarget, GLsizei howMany)
    : GLObject(howMany), mTarget(textureTarget) {
  reload();
}

Texture::~Texture() {
  glDeleteTextures(mHowMany, mHandles);
  fLogC("Could not delete texture");
}

GLint Texture::getTarget() {
  return mTarget;
}

void Texture::bind(GLuint id) {
  glBindTexture(mTarget, mHandles[id]);
  fLogC("bind (id) texture");
}

void Texture::bind(GLint textureUnit, GLuint id) {
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(mTarget, mHandles[id]);
  fLogC("bind (texUnit, id) texture");
}

void Texture::unbind() {
  glBindTexture(mTarget, 0);
  fLogC("unbind texture");
}

void Texture::setParameter(GLenum parameter, GLenum value) {
  glTexParameteri(mTarget, parameter, value);
  fLogC("setParameter");
}

void Texture::setParameters(ParameterList parameters) {
  for (auto it : parameters) {
    setParameter(it.first, it.second);
  }
}

void Texture::reload() {
  fLogD("Reload");
  glGenTextures(mHowMany, mHandles);
  fLogC("glGenTextures");
}

void bindTexture(GLuint target, GLuint handle) {
  glBindTexture(target, handle);
  fLogC("bind (id) texture");
}

void bindTexture(GLint textureUnit, GLuint target, GLuint handle) {
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(target, handle);
  fLogC("bind (texUnit, id) texture");
}

void unbindTexture(GLuint target) {
  glBindTexture(target, 0);
  fLogC("unbind texture");
}

} /* core  */
} /* flw */
