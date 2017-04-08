/*
 * Attribute.cpp
 *
 *  Created on: 2 Mar 2014
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


#include <fillwave/core/pipeline/Attribute.h>

#include <fillwave/Log.h>

FLOGINIT("Attribute", FERROR | FFATAL)

namespace flw {
namespace flc {

Attribute::Attribute(std::string name, GLuint index, GLint size, GLsizei stride, GLenum type, GLboolean normalized)
    : mStride(stride), mName(name), mIndex(index), mSize(size), mNormalized(normalized), mType(type)
    , mPointer((GLvoid *) 0) {

  switch (mType) {
    case GL_UNSIGNED_INT:
    case GL_UNSIGNED_INT_VEC2:
    case GL_UNSIGNED_INT_VEC3:
    case GL_UNSIGNED_INT_VEC4:
      //mType = GL_UNSIGNED_SHORT;
      mTypeSize = sizeof(GLuint);
      break;
    case GL_FLOAT:
    case GL_FLOAT_VEC2:
    case GL_FLOAT_VEC3:
    case GL_FLOAT_VEC4:
    case GL_FLOAT_MAT2:
    case GL_FLOAT_MAT3:
    case GL_FLOAT_MAT4:
      mTypeSize = sizeof(GLfloat);
      break;
    case GL_INT:
    case GL_INT_VEC2:
    case GL_INT_VEC3:
    case GL_INT_VEC4:
      //mType = GL_SHORT;
      mTypeSize = sizeof(GLint);
      break;
    case GL_BOOL:
    case GL_BOOL_VEC2:
    case GL_BOOL_VEC3:
    case GL_BOOL_VEC4:
      mTypeSize = sizeof(GLboolean);
      break;
    default:
      std::cout << "Not supported type of attribute" << std::endl;
      mTypeSize = sizeof(float);
      break;
  }
}

void Attribute::bindLocation(GLint programHandle) {
  glBindAttribLocation(programHandle, mIndex, mName.c_str());
  fLogC("bindAttribLocation");
}

void Attribute::arrayDisable() {
  glDisableVertexAttribArray(mIndex);
  fLogC("disableAttribLocation");
}

void Attribute::arrayEnable() {
  glEnableVertexAttribArray(mIndex);
  fLogC("enableAttribLocation");
}

void Attribute::arraySet() {
  glVertexAttribPointer(mIndex, mSize,
//                          mType,
                        GL_FLOAT, mNormalized, mStride, mPointer);
  fLogC("VertexAttribPointer");
}

void Attribute::setOffsetPointer(GLvoid *offset) {
  mPointer = offset;
}

GLuint Attribute::getSize() {
  return mSize;
}

std::size_t Attribute::getTypeSize() {
  return mTypeSize;
}

GLuint Attribute::getIndex() {
  return mIndex;
}

std::string Attribute::getName() {
  return mName;
}

void Attribute::log() {
  fLogI("mName %s", mName.c_str());
  fLogI("mType 0x%x", mType);
  fLogI("mIndex %d", mIndex);
  fLogI("mSize %d", mSize);
  fLogI("mType%d ", mType);
  fLogI("mNormalized %d", mNormalized);
  fLogI("mStride %d", mStride);
}

} /* flc */
} /* flw */
