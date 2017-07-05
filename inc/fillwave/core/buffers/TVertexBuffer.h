#pragma once

/*
* Copyright (c) 2017, Fillwave developers
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
