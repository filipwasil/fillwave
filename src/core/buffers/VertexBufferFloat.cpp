/*
 * VertexBufferFloat.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: filip
 */

#include <fillwave/core/buffers/VertexBufferFloat.h>
#include <fillwave/Log.h>

FLOGINIT("VertexBufferFloat", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferFloat::VertexBufferFloat(
   const std::vector<VertexFloat>& values,
   GLuint dataStoreModification) :
	TVertexBuffer<VertexFloat>(values, dataStoreModification) {

}

void VertexBufferFloat::log() const {
	auto d = [] (core::VertexFloat & f) {
		return static_cast<double>(f.mData);
	};
	for (auto it : mDataVertices) {
		FLOG_INFO("Vertex written: %f", d(it));
	}
}

} /* core */
} /* fillwave */
