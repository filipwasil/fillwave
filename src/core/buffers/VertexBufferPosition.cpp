/*
 * VertexBufferPosition.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: Filip Wasil
 */

#include <fillwave/core/buffers/TVertexBufferPosition.h>

FLOGINIT("VertexBufferPosition", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferPosition::VertexBufferPosition(
		framework::Shape<VertexPosition>& shape,
		GLuint dataStoreModification) :
		TVertexBuffer(shape, dataStoreModification) {

}

VertexBufferPosition::VertexBufferPosition(
		std::vector<VertexPosition>& vertices,
		GLuint dataStoreModification) :
		TVertexBuffer(vertices, dataStoreModification) {

}

void VertexBufferPosition::log() const {
	auto d = [] (GLfloat& f) {return static_cast<double>(f);};
	for (auto it : mDataVertices) {
		FLOG_INFO("Vertex written: %f %f %f %f", d(it.mPosition[0]),
			d(it.mPosition[1]), d(it.mPosition[2]), d(it.mPosition[3]));
	}
}

} /* core */
} /* fillwave*/

