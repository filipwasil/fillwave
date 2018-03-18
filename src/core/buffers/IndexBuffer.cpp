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

#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flc {

IndexBuffer::IndexBuffer(GLuint elements, bool fill, GLuint dataStoreModification)
    : IBuffer(GL_ELEMENT_ARRAY_BUFFER, dataStoreModification) {
  mTotalElements = elements;
  mDataIndices.reserve(mTotalElements);
  mSize = mTotalElements * sizeof(GLuint);
  if (fill) {
    for (GLuint i = 0; i < elements; ++i) {
      mDataIndices.push_back(i);
    }
    mData = mDataIndices.data();
  }
}

GLuint *IndexBuffer::getDataInternal() {
  if (mDataIndices.empty()) {
    fLogE("Not cpu data in this buffer");
    return nullptr;
  }
  return mDataIndices.data();
}

IndexBuffer::IndexBuffer(const std::vector<GLuint> &data, GLuint dataStoreModification)
    : IBuffer(GL_ELEMENT_ARRAY_BUFFER, dataStoreModification) {
  mTotalElements = data.size();
  mDataIndices = data;
  mSize = mTotalElements * sizeof(GLuint);
  mData = mDataIndices.data();
}

void IndexBuffer::emptyCPU() {
  mDataIndices.clear();
  mData = nullptr;
  mTotalElements = 0;
}

void IndexBuffer::emptyGPU() {
  fLogD("Not gpu data clear is possible in this buffer");
}

} /* flc */
} /* flw */
