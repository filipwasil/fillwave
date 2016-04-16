/*
 * VertexBufferParticles.h
 *
 *  Created on: Aug 30, 2014
 *      Author: Filip Wasil
 */

#ifndef VERTEXBUFFERPARTICLES_H_
#define VERTEXBUFFERPARTICLES_H_

#include <fillwave/core/buffers/TVertexBuffer.h>

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

class VertexBufferParticles: public TVertexBuffer<VertexParticle> {
 public:
	VertexBufferParticles(
	   const std::vector<GLfloat>& velocities,
	   const std::vector<GLfloat>& positions,
	   const std::vector<GLfloat>& times);
	virtual ~VertexBufferParticles() = default;
	void log() const;
};

} /* core */
} /* fillwave */

#endif /* VERTEXBUFFERPARTICLES_H_ */
