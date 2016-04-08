/*
 * IndexBuffer.h
 *
 *  Created on: 16 Apr 2015
 *      Author: Filip Wasil
 */

#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_

#include <fillwave/core/buffers/Buffer.h>

namespace fillwave {
namespace core {

/*! \class IndexBuffer
 * \brief IndexBufferObject - IBO.
 */

class IndexBuffer: public Buffer {
  public:
	IndexBuffer(GLuint elements, GLuint dataStoreModification);
	virtual ~IndexBuffer() = default;

  protected:
	std::vector<GLuint> mDataIndices;
};

} /* core */
} /* fillwave */
#endif /* INDEXBUFFER_H_ */
