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

#include <flw/flc/buffers/mVertexBufferParticles.h>
#include <flw/Log.h>

FLOGINIT("VertexBufferParticles", FERROR | FFATAL)

namespace flw {
namespace flc {

VertexBufferParticles::VertexBufferParticles(const std::vector<GLfloat> &velocities,
    const std::vector<GLfloat> &positions,
    const std::vector<GLfloat> &times) {
  size_t size = times.size();
  if (size == velocities.size() / 3) {
    mDataVertices.reserve(size);
    VertexParticle vertex;
    for (size_t i = 0; i < size; ++i) {
      vertex.velocity[0] = velocities[i * 3];
      vertex.velocity[1] = velocities[i * 3 + 1];
      vertex.velocity[2] = velocities[i * 3 + 2];
      vertex.startPosition[0] = positions[i * 3];
      vertex.startPosition[1] = positions[i * 3 + 1];
      vertex.startPosition[2] = positions[i * 3 + 2];
      vertex.startTime = times[i];
      mDataVertices.push_back(vertex);
    }
  } else {
    fLogE("Wrong buffer sizes");
    return;
  }
  mTotalElements = mDataVertices.size();
  mData = mDataVertices.data();
  mSize = mTotalElements * sizeof(VertexParticle);
}

void VertexBufferParticles::log() const {
  for (auto& it : mDataVertices) {
    fLogE("Vertex written: ", it.velocity[0], " ", it.velocity[1], " ", it.velocity[2], " ", it.startTime);
  }
}

} /* flc */
} /* flw */
