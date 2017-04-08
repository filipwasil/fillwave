/*
 * Attribute.h
 *
 *  Created on: 2 March 2014
 *      Author: Filip Wasil
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

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <fillwave/core/pipeline/Program.h>

namespace flw {
namespace flc {

/*! \class Attribute
 * \brief VertexAttribute to be kept within the VertexBuffer.
 */

class Attribute {
public:
  Attribute(std::string name, GLuint index, GLint size, GLsizei stride, GLenum type, GLboolean normalized = GL_FALSE);

  virtual ~Attribute() = default;

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
  GLvoid *mPointer;
};

} /* flc */
} /* flw */

#endif /* ATTRIBUTE_H_ */
