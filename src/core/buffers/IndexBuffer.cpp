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

/*! \class IndexBufferBasic
 * \brief IBO for regular usage.
 */

#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/Log.h>

FLOGINIT("IndexBuffer", FERROR | FFATAL)

namespace flw {
namespace flc {

IndexBuffer::IndexBuffer(GLuint elements, bool fill, GLuint dataStoreModification)
    : IBuffer(GL_ELEMENT_ARRAY_BUFFER, dataStoreModification) {
  mTotalElements = elements;
  mDataIndices.reserve(mTotalElements);
  mSize = mTotalElements * sizeof(GLuint);
  if (fill) {
    for (GLuint i = 0; i < elements; i++) {
      mDataIndices.push_back(i);
    }
    mData = mDataIndices.data();
  }
}

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

IndexBuffer::IndexBuffer(const aiMesh *shape, GLuint dataStoreModification)
    : IBuffer(GL_ELEMENT_ARRAY_BUFFER, dataStoreModification) {
  mTotalElements = shape->mNumFaces * 3;
  mDataIndices.resize(mTotalElements);

#pragma omp parallel for schedule(guided) num_threads(2) if (shape->mNumFaces > 1000)
  for (GLuint i = 0; i < shape->mNumFaces; i++) {
    const GLuint idx = 3 * i;
    mDataIndices[idx] = shape->mFaces[i].mIndices[0];
    mDataIndices[idx + 1] = shape->mFaces[i].mIndices[1];
    mDataIndices[idx + 2] = shape->mFaces[i].mIndices[2];
  }
  mSize = mTotalElements * sizeof(GLuint);
  mData = mDataIndices.data();
}

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

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
