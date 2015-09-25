/*
 * PixelBuffer.cpp
 *
 *  Created on: Jun 3, 2014
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

#include <fillwave/core/buffers/PixelBuffer.h>

namespace fillwave {
namespace core {

PixelBuffer::PixelBuffer(GLuint dataStoreType)
		: Buffer(GL_PIXEL_PACK_BUFFER, dataStoreType) {
	mData = 0;
}

PixelBuffer::~PixelBuffer() {

}

void PixelBuffer::setScreenSize(
		GLuint width,
		GLuint height,
		GLuint bytesPerPixel) {
	mSize = bytesPerPixel * width * height;
}

} /* models */
} /* fillwave */
