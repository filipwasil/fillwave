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

#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/Log.h>

FLOGINIT("VertexBufferPosition", FERROR | FFATAL)

namespace flw {
namespace flc {

VertexBufferPosition::VertexBufferPosition(flf::Shape<VertexPosition>& shape, GLuint dataStoreModification)
    : TVertexBuffer(shape, dataStoreModification) {
  // nothing
}

VertexBufferPosition::VertexBufferPosition(const std::vector<VertexPosition>& vertices, GLuint dataStoreModification)
    : TVertexBuffer(vertices, dataStoreModification) {
  // nothing
}

void VertexBufferPosition::log() const {
  for (auto it : mDataVertices) {
    fLogI("Vertex written: ", it.mPosition[0], " ", it.mPosition[1], " ", it.mPosition[2], " ", it.mPosition[3]);
  }
}

} /* flc */
} /* flw*/

