/*
 * PixelBuffer.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: filip
 */

#include <fillwave/core/buffers/PixelBuffer.h>
#include <fillwave/Log.h>

FLOGINIT("PixelBuffer", FERROR | FFATAL)

namespace fillwave {
namespace core {

PixelBuffer::PixelBuffer(GLuint dataStoreType) :
	IBuffer(GL_PIXEL_PACK_BUFFER, dataStoreType) {
	mData = 0;
}

void PixelBuffer::setScreenSize(
   GLuint width,
   GLuint height,
   GLuint bytesPerPixel) {
	mSize = bytesPerPixel * width * height;
}

void PixelBuffer::emptyCPU() {
	FLOG_DEBUG("Not gpu data clear is possible with this buffer");
}

void PixelBuffer::emptyGPU() {
	FLOG_DEBUG("Not gpu data clear is possible with this buffer");
}

} /* models */
} /* fillwave */
