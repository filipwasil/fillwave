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
#include <fillwave/Log.h>

FLOGINIT_MASK(FERROR | FFATAL | FDEBUG)

namespace flw {
namespace flc {

Texture::Texture(GLenum textureTarget, GLsizei howMany)
  : mHowMany(howMany)
  , mTarget(textureTarget) {
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

GLuint Texture::getHandle(GLuint id) {
  return id < FILLWAVE_GLOBJECTS_MAX ? mHandles[id] : 0;
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
