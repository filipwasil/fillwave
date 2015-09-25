/*
 * VertexBufferText.cpp
 *
 *  Created on: Jul 26, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
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

VertexBufferText::~VertexBufferText() {

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
