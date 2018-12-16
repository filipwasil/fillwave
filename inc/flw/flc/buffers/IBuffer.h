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

#include <flw/OpenGL.h>

namespace flw {
namespace flc {

/*! \class IBuffer
 * \brief Base for all buffer types.
 */

class IBuffer {
public:
  IBuffer(GLuint target, GLuint drawType = GL_STATIC_DRAW, GLuint index = 0, GLsizei howMany = 1);

  virtual ~IBuffer();

  void bind(GLuint id = 0) const;

  void bind(GLuint externalTarget, GLuint id) const;

  void bindBase(GLuint id = 0) const;

  void bindBase(GLuint externalTarget, GLuint id) const;

  void unbind();

  void unbindBase(GLuint externalTarget);

  void unmap() const;

  void send();

  void setTarget(GLuint target);

  void setDrawType(GLuint drawType);

  bool isLoaded();

  void setLoaded(bool loaded);

  GLsizei getElements() const;

  GLsizeiptr getSize() const;

  GLvoid *getData() const;

  void reload();

  GLvoid* mapRange(GLenum access, GLuint size = 0);

  GLvoid *map(GLenum access) const;

  virtual void emptyCPU() = 0;

  virtual void emptyGPU() = 0;

  GLuint getHandle(GLuint id = 0);

 protected:
  GLsizei mHowMany;
  GLuint mHandles[FILLWAVE_GLOBJECTS_MAX];

  bool mLoaded;
  GLuint mTarget;
  GLuint mDataStoreType;
  GLuint mIndex;
  GLvoid* mData;
  GLsizeiptr mSize;
  GLsizei mTotalElements;

  void setElements(GLsizei elements);

  void setSize(GLuint size);
};

void unbindBuffer(GLuint target);

void bindBuffer(GLuint target, GLuint handle);

} /* flc */
} /* flw */
