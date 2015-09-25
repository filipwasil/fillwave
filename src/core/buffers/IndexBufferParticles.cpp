/*
 * IndexBufferParticles.cpp
 *
 *  Created on: 16 Apr 2015
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

IndexBufferParticles::~IndexBufferParticles() {

}

GLuint* IndexBufferParticles::getDataInternal() {
	return mDataIndices.data();
}

} /* core */
} /* fillwave */
