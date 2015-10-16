/*
 * PixelBuffer.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: filip
 */

#include <fillwave/core/buffers/PixelBuffer.h>

namespace fillwave {
namespace core {

PixelBuffer::PixelBuffer(GLuint dataStoreType)
		: Buffer(GL_PIXEL_PACK_BUFFER, dataStoreType) {
	mData = 0;
}

void PixelBuffer::setScreenSize(
		GLuint width,
		GLuint height,
		GLuint bytesPerPixel) {
	mSize = bytesPerPixel * width * height;
}

} /* models */
} /* fillwave */
