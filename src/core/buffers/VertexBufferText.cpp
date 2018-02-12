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

#include <fillwave/core/buffers/VertexBufferText.h>
#include <fillwave/Log.h>

FLOGINIT("VertexBufferText", FERROR | FFATAL)

namespace flw {
namespace flc {

VertexBufferText::VertexBufferText(const std::vector<GLfloat>& positions
                                   , const std::vector<GLfloat>& textureCoords
                                   , GLuint dataStoreModification)
    : TVertexBuffer(dataStoreModification) {
  const size_t size = positions.size();
  if (size == textureCoords.size()) {
    mDataVertices.reserve(size / 2);
    VertexText vertex;
    for (size_t i = 0; i < size / 2; i++) {
      vertex.position[0] = positions[i * 2];
      vertex.position[1] = positions[i * 2 + 1];
      vertex.uv[0] = textureCoords[i * 2];
      vertex.uv[1] = textureCoords[i * 2 + 1];
      mDataVertices.push_back(vertex);
    }
  } else {
    fLogE("Wrong buffer sizes");
    return;
  }
  mTotalElements = mDataVertices.size();
  mData = mDataVertices.data();
  mSize = mTotalElements * sizeof(VertexText);
}

void VertexBufferText::log() const {
  for (auto& it : mDataVertices) {
    fLogE("Vertex written: ", it.position[0], " ", it.position[1], " ", it.uv[0], " ", it.uv[1]);
  }
}

} /* flc */
} /* flw */
