/*
 * VertexBufferDebug.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: filip
 */

#include <fillwave/core/buffers/VertexBufferDebug.h>

namespace fillwave {
namespace core {

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

} /* core */
} /* fillwave */
