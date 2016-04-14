/*
 * VertexBufferFloat.h
 *
 *  Created on: Sep 8, 2015
 *      Author: filip
 */

#ifndef SRC_CORE_BUFFERS_VERTEXBUFFERFLOAT_H_
#define SRC_CORE_BUFFERS_VERTEXBUFFERFLOAT_H_

#include <fillwave/core/buffers/TVertexBuffer.h>

namespace fillwave {
namespace core {

struct VertexFloat {
    GLfloat mData;
};

/*! \class VertexBufferFloat
 * \brief Vertex buffer specialized with GLfloat data structure.
 */
class VertexBufferFloat: public TVertexBuffer<VertexFloat> {
 public:
	VertexBufferFloat(
	   std::vector<VertexFloat>& values,
	   GLuint dataStoreModification = GL_STATIC_DRAW);
	virtual ~VertexBufferFloat() = default;
	void log() const;
};

} /* core */
} /* fillwave */

#endif /* SRC_CORE_BUFFERS_VERTEXBUFFERFLOAT_H_ */
