/*
 * VertexBufferText.cpp
 *
 *  Created on: Jul 26, 2014
 *      Author: filip
 */

#include <fillwave/core/buffers/VertexBufferText.h>
#include <fillwave/Log.h>

FLOGINIT("VertexBufferText", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferText::VertexBufferText(
		std::vector<GLfloat> positions,
		std::vector<GLfloat> textureCoords,
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
		FLOG_ERROR("Wrong buffer sizes");
		return;
	}
	mTotalElements = mDataVertices.size();
	mData = mDataVertices.data();
	mSize = mTotalElements * sizeof(VertexText);
}

void VertexBufferText::log() const {
	auto d = [] (GLfloat& f) {return static_cast<double>(f);};
	for (auto it : mDataVertices) {
		for (size_t i = 0; i < mDataVertices.size(); i++) {
			FLOG_ERROR("Vertex written: %f %f %f %f", d(it.position[0]),
				d(it.position[1]), d(it.uv[0]), d(it.uv[1]));
		}
	}
}

} /* core */
} /* fillwave */
