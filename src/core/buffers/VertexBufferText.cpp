/*
 * VertexBufferText.cpp
 *
 *  Created on: Jul 26, 2014
 *      Author: filip
 */

#include <fillwave/core/buffers/VertexBufferText.h>
#include <fillwave/extras/Log.h>

FLOGINIT("VertexBufferText", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferText::VertexBufferText(
		std::vector<GLfloat> positions,
		std::vector<GLfloat> textureCoords,
		GLuint dataStoreModification)
		: VertexBuffer(dataStoreModification) {
	GLuint size = positions.size();
	if (size == textureCoords.size()) {
		mDataVertices.reserve(size / 2);
		VertexText vertex;
		for (int i = 0; i < size / 2; i++) {
			vertex.position[0] = positions[i * 2];
			vertex.position[1] = positions[i * 2 + 1];
			vertex.uv[0] = textureCoords[i * 2];
			vertex.uv[1] = textureCoords[i * 2 + 1];
			mDataVertices.push_back(vertex);
		}
	} else {
		FLOG_ERROR("Wrong buffer sizes");
		return;
	}
	mTotalElements = mDataVertices.size();
	mData = mDataVertices.data();
	mSize = mTotalElements * sizeof(VertexText);
}

void VertexBufferText::log() {
	for (auto it : mDataVertices) {
		for (int i = 0; i < mDataVertices.size(); i++) {
			FLOG_ERROR("Vertex written: %f %f %f %f", it.position[0],
					it.position[1], it.uv[0], it.uv[1]);
		}
	}
}

} /* models */
} /* fillwave */
