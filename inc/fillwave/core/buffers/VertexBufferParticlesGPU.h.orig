/*
 * VertexBufferParticlesGPU.h
 *
 *  Created on: Aug 30, 2014
 *      Author: Filip Wasil
 */

#ifndef VertexBufferParticlesGPU_H_
#define VertexBufferParticlesGPU_H_

#include <fillwave/core/buffers/TVertexBuffer.h>

namespace fillwave {
namespace core {

/*! \struct VertexParticleGPU
 * \brief Stores the particle vertex data computed entirely on GPU.
 */

struct VertexParticleGPU {
	float position[3];
	float velocity[3];
	float size;
	float currentTime;
	float lifetime;
	float cameraDistance;
};

/*! \class VertexBufferParticlesGPU
 * \brief Vertex buffer specialized with VertexParticleGPU data structure.
 */

class VertexBufferParticlesGPU: public TVertexBuffer<VertexParticleGPU> {
public:
	VertexBufferParticlesGPU(std::vector<VertexParticleGPU>& particles);
	virtual ~VertexBufferParticlesGPU() = default;
	void log() const;
};

} /* core */
typedef std::shared_ptr<core::VertexBufferParticlesGPU> pVertexBufferParticlesGPU;
} /* fillwave */

#endif /* VertexBufferParticlesGPU_H_ */
