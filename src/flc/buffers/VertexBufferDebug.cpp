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

#include <flw/flc/buffers/mVertexBufferDebug.h>

namespace flw {
namespace flc {

VertexBufferDebug::VertexBufferDebug(float) {

  GLfloat debugWindow2DPositions[] = {
      -1.0, 1.0,
      -1.0, -1.0,
      1.0, 1.0,
      1.0, 1.0,
      -1.0, -1.0,
      1.0, -1.0
  };

  GLfloat debugWindow2DUV[] = {
      0.0, 1.0,
      0.0, 0.0,
      1.0, 1.0,
      1.0, 1.0,
      0.0, 0.0,
      1.0, 0.0
  };

  mDataVertices.reserve(6);
  VertexDebug vertex;
  for (int i = 0; i < 6; ++i) {
    const int idx = 2 * i;
    vertex.position[0] = debugWindow2DPositions[idx];
    vertex.position[1] = debugWindow2DPositions[idx + 1];
    vertex.uv[0] = debugWindow2DUV[idx];
    vertex.uv[1] = debugWindow2DUV[idx + 1];
    mDataVertices.push_back(vertex);
  }
  mTotalElements = mDataVertices.size();
  mData = mDataVertices.data();
  mSize = static_cast<GLsizeiptr>(mTotalElements * sizeof(VertexDebug));
}

void VertexBufferDebug::log() const {
  // nothing
}

} /* flc */
} /* flw */
