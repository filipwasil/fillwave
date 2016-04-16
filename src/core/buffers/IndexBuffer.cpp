/*
 * IndexBuffer.cpp
 *
 *  Created on: 16 Apr 2015
 *      Author: Filip Wasil
 */

/*! \class IndexBufferBasic
 * \brief IBO for regular usage.
 */

#include <fillwave/core/buffers/IndexBuffer.h>

FLOGINIT("IndexBuffer", FERROR | FFATAL)

namespace fillwave {
namespace core {

IndexBuffer::IndexBuffer(GLuint elements, bool fill,
                         GLuint dataStoreModification) :
	IBuffer(GL_ELEMENT_ARRAY_BUFFER, dataStoreModification) {
	mTotalElements = elements;
	mDataIndices.reserve(mTotalElements);
	mSize = mTotalElements * sizeof(GLuint);
	if (fill) {
		for (GLuint i = 0; i < elements; i++) {
			mDataIndices.push_back(i);
		}
		mData = mDataIndices.data();
	}
}

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
IndexBuffer::IndexBuffer(
   const aiMesh* shape,
   GLuint dataStoreModification) :
	IBuffer(GL_ELEMENT_ARRAY_BUFFER, dataStoreModification) {
	mTotalElements = shape->mNumFaces * 3;
//   #pragma omp parallel for schedule(guided) num_threads(2) if (shape->mNumFaces > 1000) disaster
	for (GLuint i = 0; i < shape->mNumFaces; i++) {
		mDataIndices.push_back(shape->mFaces[i].mIndices[0]);
		mDataIndices.push_back(shape->mFaces[i].mIndices[1]);
		mDataIndices.push_back(shape->mFaces[i].mIndices[2]);
	}
	mSize = mTotalElements * sizeof(GLuint);
	mData = mDataIndices.data();
}
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

GLuint* IndexBuffer::getDataInternal() {
	if (mDataIndices.empty()) {
		FLOG_ERROR("Not cpu data in this buffer");
		return nullptr;
	}
	return mDataIndices.data();
}

IndexBuffer::IndexBuffer(
   const std::vector<GLuint>& data,
   GLuint dataStoreModification) :
	IBuffer(GL_ELEMENT_ARRAY_BUFFER, dataStoreModification) {
	mTotalElements = data.size();
	mDataIndices = data;
	mSize = mTotalElements * sizeof(GLuint);
	mData = mDataIndices.data();
}

void IndexBuffer::loadElement(GLuint element) {
	mDataIndices.push_back(element);
	mTotalElements++;
	mSize = mTotalElements * sizeof(GLuint);
	mData = mDataIndices.data();
}

void IndexBuffer::emptyCPU() {
	mDataIndices.clear();
}

void IndexBuffer::emptyGPU() {
	FLOG_ERROR("Not gpu data clear is possible in this buffer");
}

} /* core */
} /* fillwave */
