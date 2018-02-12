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
#include <fillwave/core/buffers/IBuffer.h>
#include <fillwave/core/pipeline/Attribute.h>
#include <fillwave/models/shapes/Shape.h>

#include <algorithm>

namespace flw {
namespace flc {

class Attribute;

/*! \class TVertexBuffer
 * \brief Template for all vertex buffers.
 */

template <class T>
class TVertexBuffer : public IBuffer {
public:
  /* Notice
   * In this constructor one should initialize:
   *  - mDataVertices -> vector of <T> data
   *
   *  mData = mDataVertices.data();
   *  mTotalElements = mDataVertices.size();
   *  mSize = mTotalElements*sizeof(<T>);
   */

  TVertexBuffer(GLuint dataStoreModification = GL_STATIC_DRAW)
      : IBuffer(GL_ARRAY_BUFFER, dataStoreModification) {
  }

  TVertexBuffer(const std::vector<T> &vertices, GLuint dataStoreModification = GL_STATIC_DRAW)
      : IBuffer(GL_ARRAY_BUFFER, dataStoreModification) {
    mDataVertices = vertices;
    mTotalElements = mDataVertices.size();
    mData = mDataVertices.data();
    mSize = mTotalElements * sizeof(T);
  }

  TVertexBuffer(flf::Shape<T> &shape, GLuint dataStoreModification = GL_STATIC_DRAW)
      : IBuffer(GL_ARRAY_BUFFER, dataStoreModification) {
    mDataVertices = shape.getVertices();
    mSize = mTotalElements * sizeof(T);
    mData = mDataVertices.data();
  }

  ~TVertexBuffer() override = default;

  void load(T element) {
    mDataVertices.push_back(element);
    mTotalElements++;
    mSize = mTotalElements * sizeof(T);
    mData = mDataVertices.data();
  }

  void initAttributes(GLint programHandle) {
    if (mAttributes.empty()) {
      getAttributes(programHandle);
    }
    return;
  }

  void attributesSetForVAO() {
    std::for_each(mAttributes.begin(), mAttributes.end(), [](Attribute &a) {
      a.arrayEnable();
    });
    std::for_each(mAttributes.begin(), mAttributes.end(), [](Attribute &a) {
      a.arraySet();
    });
  }

  void attributesEnable() {
    std::for_each(mAttributes.begin(), mAttributes.end(), [](Attribute &a) {
      a.arrayEnable();
    });
  }

  void reload() {
    IBuffer::reload();
  }

  void attributesSetPointer() {
    std::for_each(mAttributes.begin(), mAttributes.end(), [](Attribute &a) {
      a.arraySet();
    });
  }

  T *getDataInternal() {
    if (mDataVertices.empty()) {
      std::cout << "Not cpu data in this buffer" << std::endl;
      return nullptr;
    }
    return mDataVertices.data();
  }

  void emptyCPU() override {
    mDataVertices.clear();
    mData = nullptr;
    mTotalElements = 0;
  }

  void emptyGPU() override {
    std::cout << "Not gpu data clear is possible in this buffer" << std::endl;
  }

  virtual void log() const = 0;

protected:
  std::vector<T> mDataVertices;

  inline void getAttributes(GLint programHandle) {
    int howMany = -1;
    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &howMany);
    for (int i = 0; i < howMany; ++i) {
      int name_len = -1, num = -1;
      GLenum type = GL_ZERO;
      char name[200];
      glGetActiveAttrib(programHandle, GLuint(i), sizeof(name) - 1, &name_len, &num, &type, name);
      name[name_len] = 0;
      GLuint location = glGetAttribLocation(programHandle, name);
      GLuint size = 0;
      switch (type) {
        case GL_UNSIGNED_INT:
        case GL_FLOAT:
        case GL_INT:
        case GL_BOOL:
          size = 1;
          break;
        case GL_FLOAT_VEC2:
        case GL_INT_VEC2:
        case GL_BOOL_VEC2:
          size = 2;
          break;
        case GL_FLOAT_VEC3:
        case GL_INT_VEC3:
        case GL_BOOL_VEC3:
          size = 3;
          break;
        case GL_FLOAT_VEC4:
        case GL_INT_VEC4:
        case GL_BOOL_VEC4:
        case GL_FLOAT_MAT2:
          size = 4;
          break;
        case GL_FLOAT_MAT3:
          size = 9;
          break;
        case GL_FLOAT_MAT4:
          size = 16;
          break;
//#ifdef FILLWAVE_GLES_3_0
//#else
        case GL_UNSIGNED_INT_VEC3:
          size = 3;
          break;
        case GL_UNSIGNED_INT_VEC2:
          size = 2;
          break;
        case GL_UNSIGNED_INT_VEC4:
          size = 4;
          break;
//#endif
        default:
          std::cout << "Not supported type of attribute" << std::endl;
          size = 0;
          break;
      }
      Attribute a(name, location, size, sizeof(T), type);
      mAttributes.push_back(a);
    }

    unsigned long long pointer = 0;
    for (GLuint i = 0; i < mAttributes.size(); i++) {
      for (auto &it : mAttributes) {
        if (it.getIndex() == i) {
          it.setOffsetPointer((GLvoid *) pointer);
          pointer += it.getSize() * it.getTypeSize();
        }
      }
    }
  }

  inline void attributesBind(GLint programHandle) {
    std::for_each(mAttributes.begin(), mAttributes.end(), [programHandle](Attribute &a) {
      a.bindLocation(programHandle);
    });
  }

private:
  std::vector<Attribute> mAttributes;
};

} /* flc */
} /* flw */
