/*
 * VertexBufferDebug.cpp
 *
 *  Created on: Aug 9, 2014
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

#include <fillwave/core/buffers/VertexBufferDebug.h>

namespace fillwave {
namespace core {

VertexBufferDebug::VertexBufferDebug(GLfloat scale) {

   GLfloat debugWindow2DPositions[] = {
      -1.0,  1.0,
      -1.0, -1.0,
       1.0,  1.0,
       1.0,  1.0,
      -1.0, -1.0,
       1.0, -1.0
   };

   GLfloat debugWindow2DUV[] = {
       0.0,  1.0,
       0.0,  0.0,
       1.0,  1.0,
       1.0,  1.0,
       0.0,  0.0,
       1.0,  0.0
   };

   mDataVertices.reserve(6);
   VertexDebug vertex;
   for (int i=0; i<6; i++) {
         vertex.position[0] = debugWindow2DPositions[2*i];
         vertex.position[1] = debugWindow2DPositions[2*i + 1];
         vertex.uv[0] = debugWindow2DUV[2*i];
         vertex.uv[1] = debugWindow2DUV[2*i + 1];
         mDataVertices.push_back(vertex);
   }
   mTotalElements = mDataVertices.size();
   mData = mDataVertices.data();
   mSize = mTotalElements*sizeof(VertexDebug);
}

VertexBufferDebug::~VertexBufferDebug() {

}

void VertexBufferDebug::log() {

}

} /* core */
} /* fillwave */
