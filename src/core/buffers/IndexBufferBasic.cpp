/*
 * IndexBufferBasic.cpp
 *
 *  Created on: May 17, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/core/buffers/IndexBufferBasic.h>
#include <fillwave/extras/Log.h>

FLOGINIT("IndexBufferBasic", FERROR | FFATAL)

namespace fillwave {
namespace core {

IndexBufferBasic::IndexBufferBasic(std::vector<GLuint>& data, GLuint dataStoreModification)
:IndexBuffer(data.size(), dataStoreModification) {
   mDataIndices = data;
   mSize = mTotalElements * sizeof(GLuint);
   mData = mDataIndices.data();
}

IndexBufferBasic::IndexBufferBasic(const fMesh* shape,
                                   GLuint dataStoreModification):IndexBuffer(shape->mNumFaces*3, dataStoreModification) {
//   #pragma omp parallel for schedule(guided) num_threads(2) if (shape->mNumFaces > 1000) disaster
   for ( GLuint i=0; i<shape->mNumFaces ;i++) {
      mDataIndices.push_back(shape->mFaces[i].mIndices[0]);
      mDataIndices.push_back(shape->mFaces[i].mIndices[1]);
      mDataIndices.push_back(shape->mFaces[i].mIndices[2]);
   }
   mData = mDataIndices.data();
}

IndexBufferBasic::~IndexBufferBasic() {
}

void IndexBufferBasic::loadElement(GLuint element){//todo type buffer data
   mDataIndices.push_back(element);
   mTotalElements++;
   mSize = mTotalElements * sizeof(GLuint);
   mData = mDataIndices.data();
}

} /* core */
} /* fillwave */
