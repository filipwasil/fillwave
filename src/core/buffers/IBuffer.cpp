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


#include <fillwave/core/buffers/IBuffer.h>
#include <fillwave/Log.h>

FLOGINIT("Buffer", FERROR | FFATAL)

using namespace std;

namespace flw {
namespace flc {

IBuffer::IBuffer(GLuint target, GLuint drawType, GLuint index, GLsizei howMany)
    : GLObject(howMany)
    , mLoaded(GL_FALSE)
    , mIndex(index) {
  setTarget(target);
  setDrawType(drawType);
  reload();
}

IBuffer::~IBuffer() {
  glDeleteBuffers(mHowMany, mHandles);
}

void IBuffer::setElements(GLuint elements) {
  mTotalElements = elements;
}

void IBuffer::setSize(GLuint size) {
  mSize = size;
}

void IBuffer::setTarget(GLuint target) {
  if (target == GL_ARRAY_BUFFER_BINDING || target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER ||
      target == GL_UNIFORM_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER_BINDING || target == GL_PIXEL_PACK_BUFFER) {
    mTarget = target;
  } else {
    fLogE("Invalid target %d", mTarget);
  }
}

void IBuffer::setDrawType(GLuint dataStoreType) {
  if (dataStoreType == GL_STREAM_DRAW || dataStoreType == GL_STREAM_READ || dataStoreType == GL_STREAM_COPY ||
      dataStoreType == GL_STATIC_DRAW || dataStoreType == GL_STATIC_READ || dataStoreType == GL_STATIC_COPY ||
      dataStoreType == GL_DYNAMIC_DRAW || dataStoreType == GL_DYNAMIC_READ || dataStoreType == GL_DYNAMIC_COPY) {
    mDataStoreType = dataStoreType;
  } else {
    fLogE("Invalid data store type %d", mTarget);
  }
}

bool IBuffer::isLoaded() {
  return mLoaded;
}

void IBuffer::setLoaded(bool loaded) {
  mLoaded = loaded;
}

GLuint IBuffer::getElements() const {
  return mTotalElements;
}

GLuint IBuffer::getSize() const {
  return mSize;
}

GLvoid *IBuffer::getData() const {
  return mData;
}

void IBuffer::unmap() const {
  glUnmapBuffer(mTarget);
  fLogC("Could not unmap the buffer object");
}

void IBuffer::bind(GLuint id) const {
  glBindBuffer(mTarget, mHandles[id]);
  fLogC("Could not bind the buffer object");
}

void IBuffer::bindBase(GLuint id) const {
  glBindBufferBase(mTarget, mIndex, mHandles[id]);
  fLogC("Bind the uniform buffer object");
}

void IBuffer::unbind() {
  glBindBuffer(mTarget, 0);
  fLogC("Could not unbind the buffer object");
}

void IBuffer::bind(GLuint externalTarget, GLuint id) const {
  glBindBuffer(externalTarget, mHandles[id]);
  fLogC("Could not bind the buffer object");
}

void IBuffer::bindBase(GLuint externalTarget, GLuint id) const {
  glBindBufferBase(externalTarget, mIndex, mHandles[id]);
  fLogC("Bind the uniform buffer object");
}

void IBuffer::unbindBase(GLuint externalTarget) {
  glBindBufferBase(externalTarget, mIndex, 0);
  fLogC("Could not unbind the buffer object");
}

void IBuffer::send() {
  if (!mLoaded) {
    glBufferData(mTarget, mSize, mData, mDataStoreType);
    mLoaded = GL_TRUE;
    fLogC("Could not send the data");
  }
}

GLvoid *IBuffer::mapRange(GLenum access, GLuint size) {
  GLvoid *ptr = nullptr;
  if (size) {
    ptr = glMapBufferRange(mTarget, 0, size, access);
    fLogC("Could not map range of the buffer object");
  } else {
    ptr = glMapBufferRange(mTarget, 0, mSize, access);
    fLogC("Could not map range of the buffer object");
  }
  return ptr;
}

void IBuffer::reload() {
  glGenBuffers(mHowMany, mHandles);
  fLogC("reload");
}

/* Feature not available in OpenGL ES  < 3.1 */
#ifdef FILLWAVE_GLES_3_0
#else

GLvoid* IBuffer::map(GLenum access) const {
  GLvoid *ptr = glMapBuffer(mTarget, access);
  fLogC("Could not map the buffer object");
  return ptr;
}

#endif

void unbindBuffer(GLuint target) {
  glBindBuffer(target, 0);
  fLogC("Could not unbind the buffer object");
}

void bindBuffer(GLuint target, GLuint handle) {
  glBindBuffer(target, handle);
  fLogC("Could not bind the buffer object");
}

} /* flc */
} /* flw */
