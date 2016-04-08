/*
 * VertexBufferParticles.cpp
 *
 *  Created on: Aug 30, 2014
 *      Author: filip
 */

#include <fillwave/core/buffers/VertexBufferParticles.h>
#include <fillwave/Log.h>

FLOGINIT("VertexBufferParticles", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferParticles::VertexBufferParticles(
    std::vector<GLfloat>& velocities,
    std::vector<GLfloat>& positions,
    std::vector<GLfloat>& times) {
	size_t size = times.size();
	if (size == velocities.size() / 3) {
		mDataVertices.reserve(size);
		VertexParticle vertex;
		for (size_t i = 0; i < size; i++) {
			vertex.velocity[0] = velocities[i * 3];
			vertex.velocity[1] = velocities[i * 3 + 1];
			vertex.velocity[2] = velocities[i * 3 + 2];
			vertex.startPosition[0] = positions[i * 3];
			vertex.startPosition[1] = positions[i * 3 + 1];
			vertex.startPosition[2] = positions[i * 3 + 2];
			vertex.startTime = times[i];
			mDataVertices.push_back(vertex);
		}
	} else {
		FLOG_ERROR("Wrong buffer sizes");
		return;
	}
	mTotalElements = mDataVertices.size();
	mData = mDataVertices.data();
	mSize = mTotalElements * sizeof(VertexParticle);
}

void VertexBufferParticles::log() const {
	auto d = [] (GLfloat & f) {
		return static_cast<double>(f);
	};
	for (auto it : mDataVertices) {
		FLOG_ERROR("Vertex written: %f %f %f %f", d(it.velocity[0]),
		           d(it.velocity[1]), d(it.velocity[2]), d(it.startTime));
	}
}

} /* core */
} /* fillwave */
