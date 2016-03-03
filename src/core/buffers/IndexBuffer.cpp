/*
 * IndexBuffer.cpp
 *
 *  Created on: 16 Apr 2015
 *      Author: Filip Wasil
 */

/*! \class IndexBufferBasic
 * \brief IBO for regular usage.
 */

#include <fillwave/core/buffers/IndexBuffer.h>

namespace fillwave {
namespace core {

IndexBuffer::IndexBuffer(GLuint elements, GLuint dataStoreModification) :
		Buffer(GL_ELEMENT_ARRAY_BUFFER, dataStoreModification) {
	mTotalElements = elements;
	mDataIndices.reserve(mTotalElements);
	mSize = mTotalElements * sizeof(GLuint);
}

} /* core */
} /* fillwave */
