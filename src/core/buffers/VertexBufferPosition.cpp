/*
 * VertexBufferPosition.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: Filip Wasil
 */

#include <fillwave/core/buffers/VertexBufferPosition.h>

FLOGINIT("VertexBufferPosition", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferPosition::VertexBufferPosition(
		models::Shape<VertexPosition>& shape,
		GLuint dataStoreModification)
		: VertexBuffer<VertexPosition>(shape, dataStoreModification) {

}

VertexBufferPosition::VertexBufferPosition(
		std::vector<VertexPosition>& vertices,
		GLuint dataStoreModification)
		: VertexBuffer<VertexPosition>(vertices, dataStoreModification) {

}

void VertexBufferPosition::log() {
	for (auto it : mDataVertices) {
		FLOG_INFO("Vertex written: %f %f %f %f", it.mPosition[0], it.mPosition[1],
				it.mPosition[2], it.mPosition[3]);
	}
}

} /* core */
} /* fillwave*/

