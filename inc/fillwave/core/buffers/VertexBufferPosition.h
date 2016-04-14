/*
 * VertexBufferPosition.h
 *
 *  Created on: Dec 7, 2014
 *      Author: Filip Wasil
 */

#ifndef VertexBufferPosition_H_
#define VertexBufferPosition_H_

#include <fillwave/core/buffers/TVertexBuffer.h>

namespace fillwave {
namespace core {

/*! \struct VertexPosition
 * \brief Not used. Stores the position vertex data.
 */

struct VertexPosition {
	GLfloat mPosition[4];
};

/*! \class VertexBufferPosition
 * \brief Not used. Vertex buffer specialized with VertexPosition data structure.
 */

class VertexBufferPosition: public TVertexBuffer<VertexPosition> {
 public:
	VertexBufferPosition(
	   framework::Shape<VertexPosition>& shape,
	   GLuint dataStoreModification = GL_STATIC_DRAW);
	VertexBufferPosition(
	   std::vector<VertexPosition>& vertices,
	   GLuint dataStoreModification = GL_STATIC_DRAW);
	virtual ~VertexBufferPosition() = default;
	void log() const;
};

} /* core */
} /* fillwave*/

#endif /* VertexBufferPosition_H_ */
