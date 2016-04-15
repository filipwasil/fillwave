/*
 * IndexBuffer.h
 *
 *  Created on: 16 Apr 2015
 *      Author: Filip Wasil
 */

#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_

#include <fillwave/core/buffers/IBuffer.h>
#include <fillwave/Assets.h>

namespace fillwave {
namespace core {

/*! \class IndexBuffer
 * \brief IndexBufferObject - IBO.
 */

class IndexBuffer: public IBuffer {
 public:
	// xxx fill - fills buffer with sequential data
	IndexBuffer(GLuint elements, bool fill, GLuint dataStoreModification = GL_STATIC_DRAW);
	IndexBuffer(const std::vector<GLuint>& data, GLuint dataStoreModification  = GL_STATIC_DRAW);
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	IndexBuffer(const aiMesh* shape, GLuint dataStoreModification = GL_STATIC_DRAW);
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

	virtual ~IndexBuffer() = default;

	GLuint* getDataInternal();
	void loadElement(GLuint element);

 protected:
	std::vector<GLuint> mDataIndices;
};

} /* core */
} /* fillwave */
#endif /* INDEXBUFFER_H_ */
