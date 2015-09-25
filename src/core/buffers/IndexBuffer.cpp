/*
 * IndexBuffer.cpp
 *
 *  Created on: 16 Apr 2015
 *      Author: Filip Wasil
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

/*! \class IndexBufferBasic
 * \brief IBO for regular usage.
 */

#include <fillwave/core/buffers/IndexBuffer.h>

namespace fillwave {
namespace core {

IndexBuffer::IndexBuffer(GLuint elements, GLuint dataStoreModification)
		: Buffer(GL_ELEMENT_ARRAY_BUFFER, dataStoreModification) {
	mTotalElements = elements;
	mDataIndices.reserve(mTotalElements);
	mSize = mTotalElements * sizeof(GLuint);
}

IndexBuffer::~IndexBuffer() {

}

} /* core */
} /* fillwave */
