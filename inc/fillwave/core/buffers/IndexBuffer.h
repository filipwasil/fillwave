/*
 * IndexBuffer.h
 *
 *  Created on: 16 Apr 2015
 *      Author: Filip Wasil
 */

#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_

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

/*! \class IndexBuffer
 * \brief IndexBufferObject - IBO.
 */

class IndexBuffer: public Buffer {
public:
   IndexBuffer(GLuint elements, GLuint dataStoreModification);
   virtual ~IndexBuffer();

protected:
   std::vector<GLuint> mDataIndices;
};

} /* core */
} /* fillwave */
#endif /* INDEXBUFFER_H_ */
