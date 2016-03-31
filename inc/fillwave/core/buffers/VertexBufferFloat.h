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

/*! \class VertexBufferFloat
 * \brief Vertex buffer specialized with GLfloat data structure.
 */
class VertexBufferFloat: public TVertexBuffer<GLfloat> {
public:
	VertexBufferFloat(
			std::vector<GLfloat>& values,
			GLuint dataStoreModification = GL_STATIC_DRAW);
	virtual ~VertexBufferFloat() = default;
	void log();
};

} /* core */
typedef std::shared_ptr<core::VertexBufferFloat> pVertexBufferFloat;
} /* fillwave */

#endif /* SRC_CORE_BUFFERS_VERTEXBUFFERFLOAT_H_ */
