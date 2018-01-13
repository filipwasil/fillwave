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

#include <fillwave/core/pipeline/UniformBuffer.h>
#include <fillwave/Log.h>

FLOGINIT("UniformBuffer", FERROR | FFATAL)

namespace flw {
namespace flc {

UniformBuffer::UniformBuffer(std::string name,
    GLuint index,
    GLuint uniformBlockSize,
    GLuint bindingPoint,
    GLuint dataStoreModification)
    : IBuffer(GL_UNIFORM_BUFFER, dataStoreModification, index)
    , mName(name)
    , mBindingPoint(bindingPoint) {
  bind();
  bindBase();
  unbind();
  mSize = uniformBlockSize;
}

UniformBuffer::~UniformBuffer() {
  // nothing
}

void UniformBuffer::bindRange(GLuint id) {
  return glBindBufferRange(mTarget, mBindingPoint, mHandles[id], 0, mSize);
}

void UniformBuffer::push(GLfloat *data) {
  bind();
  mData = data;
  send();
  mLoaded = GL_FALSE;
  unbind();
}

std::string UniformBuffer::getName() {
  return mName;
}

void UniformBuffer::emptyCPU() {
  fLogD("Not cpu data clear is possible in this buffer");
}

void UniformBuffer::emptyGPU() {
  fLogD("Not gpu data clear is possible in this buffer");
}

} /* flc */
} /* flw */
