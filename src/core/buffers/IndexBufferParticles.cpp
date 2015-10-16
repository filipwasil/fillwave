/*
 * IndexBufferParticles.cpp
 *
 *  Created on: 16 Apr 2015
 *      Author: filip
 */

#include <fillwave/core/buffers/IndexBufferParticles.h>

namespace fillwave {
namespace core {

IndexBufferParticles::IndexBufferParticles(GLuint elements)
		: IndexBuffer(elements, GL_STATIC_DRAW) {
	for (GLuint i = 0; i < elements; i++) {
		mDataIndices.push_back(i);
	}
	mData = mDataIndices.data();
}

GLuint* IndexBufferParticles::getDataInternal() {
	return mDataIndices.data();
}

} /* core */
} /* fillwave */
