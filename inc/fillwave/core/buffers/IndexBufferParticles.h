/*
 * IndexBufferParticles.h
 *
 *  Created on: 16 Apr 2015
 *      Author: filip
 */

#ifndef INDEXBUFFERPARTICLES_H_
#define INDEXBUFFERPARTICLES_H_

#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/Math.h>

namespace fillwave {
namespace core {

/*! \class IndexBufferParticles
 * \brief IBO to use with particles.
 */

class IndexBufferParticles: public IndexBuffer {
 public:
	IndexBufferParticles(GLuint elements);
	virtual ~IndexBufferParticles() = default;
	GLuint* getDataInternal();
};

} /* core */
typedef std::shared_ptr<core::IndexBufferParticles> pIndexBufferParticles;
} /* fillwave */

#endif /* INDEXBUFFERPARTICLES_H_ */
