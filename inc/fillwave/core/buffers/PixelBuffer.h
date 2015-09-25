/*
 * PixelBuffer.h
 *
 *  Created on: Jun 3, 2014
 *      Author: filip
 */

#ifndef PIXELBUFFER_H_
#define PIXELBUFFER_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/buffers/Buffer.h>

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

class PixelBuffer: public Buffer {
public:
   PixelBuffer(GLuint dataStoreType);
   virtual ~PixelBuffer();
   void setScreenSize(GLuint width, GLuint height, GLuint bytesPerPixel);
};

} /* core */
typedef std::shared_ptr<core::PixelBuffer> pPixelBuffer;
typedef std::unique_ptr<core::PixelBuffer> puPixelBuffer;
} /* fillwave */

#endif /* PIXELBUFFER_H_ */
