/*
 * IndexBufferBasic.h
 *
 *  Created on: 17 May, 2014
 *      Author: Filip Wasil
 */

#ifndef INDEXBUFFERBASIC_H_
#define INDEXBUFFERBASIC_H_

#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/models/shapes/Shape.h>
#include <fillwave/Assets.h>

namespace fillwave {
namespace core {

/*! \class IndexBufferBasic
 * \brief IndexBuffer for regular usage.
 */

class IndexBufferBasic: public IndexBuffer {
 public:
	IndexBufferBasic(std::vector<GLuint>& data, GLuint dataStoreModification =
	                    GL_STATIC_DRAW);

	template <class T>
	IndexBufferBasic(framework::Shape<T>& shape, GLuint dataStoreModification =
	                    GL_STATIC_DRAW) :
		IndexBuffer(shape.getIndicesSize(), dataStoreModification) {
		mDataIndices = shape.getIndices();
		mData = mDataIndices.data();
	}

	virtual ~IndexBufferBasic() = default;

	void loadElement(GLuint element);

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	IndexBufferBasic(const aiMesh* shape, GLuint dataStoreModification =
	                    GL_STATIC_DRAW);
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

};

} /* core */
} /* fillwave */

#endif /* INDEXBUFFERBASIC_H_ */
