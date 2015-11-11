/*
 * VertexBufferFloat.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: filip
 */

#include <fillwave/core/buffers/VertexBufferFloat.h>

FLOGINIT("VertexBufferFloat", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferFloat::VertexBufferFloat(
		std::vector<GLfloat>& values,
		GLuint dataStoreModification)
		: VertexBuffer<GLfloat>(values, dataStoreModification) {

}

void VertexBufferFloat::log() {
	auto d = [] (GLfloat& f) { return static_cast<double>(f); };
	for (auto it : mDataVertices) {
		FLOG_INFO("Vertex written: %f", d(it));
	}
}

} /* core */
} /* fillwave */
