/*
 * VertexBufferDebug.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: filip
 *
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


#include <fillwave/core/buffers/VertexBufferDebug.h>

namespace flw {
namespace flc {

VertexBufferDebug::VertexBufferDebug(GLfloat) {

  GLfloat debugWindow2DPositions[] = {
      -1.0,
      1.0,
      -1.0,
      -1.0,
      1.0,
      1.0,
      1.0,
      1.0,
      -1.0,
      -1.0,
      1.0,
      -1.0
  };

  GLfloat debugWindow2DUV[] = {
      0.0,
      1.0,
      0.0,
      0.0,
      1.0,
      1.0,
      1.0,
      1.0,
      0.0,
      0.0,
      1.0,
      0.0
  };

  mDataVertices.reserve(6);
  VertexDebug vertex;
  for (int i = 0; i < 6; i++) {
    vertex.position[0] = debugWindow2DPositions[2 * i];
    vertex.position[1] = debugWindow2DPositions[2 * i + 1];
    vertex.uv[0] = debugWindow2DUV[2 * i];
    vertex.uv[1] = debugWindow2DUV[2 * i + 1];
    mDataVertices.push_back(vertex);
  }
  mTotalElements = mDataVertices.size();
  mData = mDataVertices.data();
  mSize = mTotalElements * sizeof(VertexDebug);
}

void VertexBufferDebug::log() const {

}

} /* flc */
} /* flw */
