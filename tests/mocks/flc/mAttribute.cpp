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

#include <flw/flc/pipeline/Attribute.h>

namespace flw {
namespace flc {

Attribute::Attribute()
    : mStride(0)
    , mName("")
    , mIndex(0)
    , mSize(0)
    , mNormalized(0)
    , mTypeSize(0)
    , mType(0)
    , mPointer((GLvoid *) 0) {
  // nothing
}

Attribute::Attribute(const std::string& name, GLuint index, GLint size, GLsizei stride, GLenum type, GLboolean normalized)
  : mStride(stride)
  , mName(name)
  , mIndex(index)
  , mSize(size)
  , mNormalized(normalized)
  , mType(type)
  , mPointer((GLvoid *) 0) {

  switch (mType) {
    case GL_UNSIGNED_INT:
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
    case GL_UNSIGNED_INT_VEC2:
    case GL_UNSIGNED_INT_VEC3:
    case GL_UNSIGNED_INT_VEC4:
#endif
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
      mTypeSize = sizeof(GLint);
      break;
    case GL_BOOL:
    case GL_BOOL_VEC2:
    case GL_BOOL_VEC3:
    case GL_BOOL_VEC4:
      mTypeSize = sizeof(GLboolean);
      break;
    default:
      mTypeSize = sizeof(float);
      break;
  }
}

void Attribute::bindLocation(GLint programHandle) {

}

void Attribute::arrayDisable() {

}

void Attribute::arrayEnable() {

}

void Attribute::arraySet() {

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

}

} /* flc */
} /* flw */
