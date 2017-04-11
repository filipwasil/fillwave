/*
 * VertexBufferParticles.cpp
 *
 *  Created on: Aug 30, 2014
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


#include <fillwave/core/buffers/VertexBufferParticles.h>
#include <fillwave/Log.h>

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
    for (size_t i = 0; i < size; i++) {
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
  auto d = [](GLfloat &f) {
    return static_cast<double>(f);
  };
  for (auto it : mDataVertices) {
    fLogE("Vertex written: %f %f %f %f", d(it.velocity[0]), d(it.velocity[1]), d(it.velocity[2]), d(it.startTime));
  }
}

} /* flc */
} /* flw */
