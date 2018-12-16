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

#include <flw/flc/pipeline/Program.h>

namespace flw {
namespace flc {

/*! \class Attribute
 * \brief VertexAttribute to be kept within the VertexBuffer.
 */

class Attribute final {
public:
  Attribute();

  Attribute(
    const std::string& name
    , GLuint index
    , GLint size
    , GLsizei stride
    , GLenum type
    , GLboolean normalized = GL_FALSE);

  void bindLocation(GLint programHandle);

  void arrayDisable();

  void arrayEnable();

  void arraySet();

  void setOffsetPointer(GLvoid *offset);

  GLuint getSize();

  std::size_t getTypeSize();

  GLuint getIndex();

  std::string getName();

  void log();

private:
  GLsizei mStride;
  std::string mName;
  GLuint mIndex;
  GLint mSize;
  GLboolean mNormalized;
  std::size_t mTypeSize;
  GLenum mType;
  GLvoid* mPointer;
};

} /* flc */
} /* flw */
