/*
 * VertexBufferText.cpp
 *
 *  Created on: Jul 26, 2014
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
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


#include <fillwave/core/buffers/VertexBufferText.h>
#include <fillwave/Log.h>

FLOGINIT("VertexBufferText", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferText::VertexBufferText(
   const std::vector<GLfloat>& positions,
   const std::vector<GLfloat>& textureCoords,
   GLuint dataStoreModification) :
	TVertexBuffer(dataStoreModification) {
	size_t size = positions.size();
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
		FLOG_ERROR("Wrong buffer sizes",NULL);
		return;
	}
	mTotalElements = mDataVertices.size();
	mData = mDataVertices.data();
	mSize = mTotalElements * sizeof(VertexText);
}

void VertexBufferText::log() const {
	auto d = [] (GLfloat & f) {
		return static_cast<double>(f);
	};
	for (auto it : mDataVertices) {
		for (size_t i = 0; i < mDataVertices.size(); i++) {
			FLOG_ERROR("Vertex written: %f %f %f %f", d(it.position[0]),
			           d(it.position[1]), d(it.uv[0]), d(it.uv[1]));
		}
	}
}

} /* core */
} /* fillwave */
