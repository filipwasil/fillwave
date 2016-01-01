/*
 * VertexBufferDebug.h
 *
 *  Created on: Aug 9, 2014
 *      Author: Filip Wasil
 */

#ifndef VERTEXBUFFERDEBUG_H_
#define VERTEXBUFFERDEBUG_H_

#include <fillwave/core/buffers/VertexBuffer.h>

namespace fillwave {
namespace core {

/*! \struct VertexDebug
 * \brief Stores the debugger vertex data.
 */

struct VertexDebug {
	float position[2];
	float uv[2];
};

/*! \class VertexBufferDebug
 * \brief Vertex buffer specialized with VertexDebug data structure.
 */

class VertexBufferDebug: public VertexBuffer<VertexDebug> {

public:
	VertexBufferDebug(GLfloat scale = 1.0);
	virtual ~VertexBufferDebug() = default;
	void log() const;
};

} /* core */
typedef std::shared_ptr<core::VertexBufferDebug> pVertexBufferDebug;
} /* fillwave */

#endif /* VERTEXBUFFERDEBUG_H_ */
