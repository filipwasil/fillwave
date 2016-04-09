/*
 * IndexBufferBasic.cpp
 *
 *  Created on: May 17, 2014
 *      Author: filip
 */

#include <fillwave/core/buffers/IndexBufferBasic.h>
#include <fillwave/Log.h>

FLOGINIT("IndexBufferBasic", FERROR | FFATAL)

namespace fillwave {
namespace core {

IndexBufferBasic::IndexBufferBasic(
   std::vector<GLuint>& data,
   GLuint dataStoreModification) :
	IndexBuffer(data.size(), dataStoreModification) {
	mDataIndices = data;
	mSize = mTotalElements * sizeof(GLuint);
	mData = mDataIndices.data();
}

IndexBufferBasic::IndexBufferBasic(
   const fMesh* shape,
   GLuint dataStoreModification) :
	IndexBuffer(shape->mNumFaces * 3, dataStoreModification) {
//   #pragma omp parallel for schedule(guided) num_threads(2) if (shape->mNumFaces > 1000) disaster
	for (GLuint i = 0; i < shape->mNumFaces; i++) {
		mDataIndices.push_back(shape->mFaces[i].mIndices[0]);
		mDataIndices.push_back(shape->mFaces[i].mIndices[1]);
		mDataIndices.push_back(shape->mFaces[i].mIndices[2]);
	}
	mData = mDataIndices.data();
}

void IndexBufferBasic::loadElement(GLuint element) {
	mDataIndices.push_back(element);
	mTotalElements++;
	mSize = mTotalElements * sizeof(GLuint);
	mData = mDataIndices.data();
}

} /* core */
} /* fillwave */
