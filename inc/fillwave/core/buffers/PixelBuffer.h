/*
 * PixelBuffer.h
 *
 *  Created on: Jun 3, 2014
 *      Author: filip
 */

#ifndef PIXELBUFFER_H_
#define PIXELBUFFER_H_

#include <fillwave/core/buffers/IBuffer.h>

namespace fillwave {
namespace core {

/*! \class PixelBuffer
 * \brief PixelBufferObject - PBO. Used to read pixels from FBO.
 */

/*
 * When using a PBO as target for glReadPixels
 * you have to specify a byte offset into the buffer
 * just like in glVertexPointer in VBO.
 *
 */

class PixelBuffer: public IBuffer {
 public:
	PixelBuffer(GLuint dataStoreType);
	virtual ~PixelBuffer() = default;
	void setScreenSize(GLuint width, GLuint height, GLuint bytesPerPixel);
};

} /* core */
typedef std::shared_ptr<core::PixelBuffer> pPixelBuffer;
typedef std::unique_ptr<core::PixelBuffer> puPixelBuffer;
} /* fillwave */

#endif /* PIXELBUFFER_H_ */
