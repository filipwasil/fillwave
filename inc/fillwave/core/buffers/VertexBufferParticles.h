/*
 * VertexBufferParticles.h
 *
 *  Created on: Aug 30, 2014
 *      Author: Filip Wasil
 */

#ifndef VERTEXBUFFERPARTICLES_H_
#define VERTEXBUFFERPARTICLES_H_

#include <fillwave/core/buffers/VertexBuffer.h>

namespace fillwave {
namespace core {

/*! \struct VertexParticle
 * \brief Stores the particle vertex data.
 */

struct VertexParticle {
	float velocity[3];
	float startPosition[3];
	float startTime;
};

/*! \class VertexBufferParticles
 * \brief Vertex buffer specialized with VertexParticle data structure.
 */

class VertexBufferParticles: public VertexBuffer<VertexParticle> {
public:
	VertexBufferParticles(
			std::vector<GLfloat>& velocities,
			std::vector<GLfloat>& positions,
			std::vector<GLfloat>& times);
	virtual ~VertexBufferParticles() = default;
	void log();
};

} /* core */
typedef std::shared_ptr<core::VertexBufferParticles> pVertexBufferParticles;
} /* fillwave */

#endif /* VERTEXBUFFERPARTICLES_H_ */
