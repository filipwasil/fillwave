/*
 * Copyright (c) 2018, Fillwave developers
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

#include <fillwave/core/texturing/Sampler.h>
#include <fillwave/Log.h>

FLOGINIT("Sampler", FERROR | FFATAL)

namespace flw {
namespace flc {

Sampler::Sampler(GLint textureUnit, GLuint howMany)
    : GLObject(howMany)
    , mTextureUnit(textureUnit) {
  glGenSamplers(mHowMany, mHandles);
  fLogC("ERROR: Could not generate sampler -> ID");
}

Sampler::~Sampler() {
  glDeleteSamplers(mHowMany, mHandles);
}

void Sampler::bind(GLuint id) {
  glBindSampler(mTextureUnit, mHandles[id]);
  fLogC("Could not bind the Sampler");
}

void Sampler::unbind(GLuint id) {
  glBindSampler(0, mHandles[id]);
  fLogC("Could not bind the VAO");
}

void Sampler::setParameters(ParameterList parameters) {
  for (auto& it : parameters) {
    setParameter(it.first, it.second);
  }
}

void Sampler::setParameter(GLenum parameter, GLenum value, GLuint id) {
  glSamplerParameteri(mHandles[id], parameter, value);
  fLogC("setParameter: ", parameter);
}

void Sampler::setParameter(Parameter parameter, GLuint id) {
  glSamplerParameteri(mHandles[id], parameter.first, parameter.second);
  fLogC("setParameter");
}

GLint Sampler::getTextureUnit() {
  return mTextureUnit;
}

void Sampler::reload() {
  glGenSamplers(mHowMany, mHandles);
  fLogC("reload");
}

} /* flc */
} /* flw */
