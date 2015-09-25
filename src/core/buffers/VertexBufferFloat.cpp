/*
 * VertexBufferFloat.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/buffers/VertexBufferFloat.h>

FLOGINIT("VertexBufferFloat", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferFloat::VertexBufferFloat(std::vector<GLfloat>& values, GLuint dataStoreModification)
:VertexBuffer<GLfloat>(values, dataStoreModification) {

}

VertexBufferFloat::~VertexBufferFloat() {

}

void VertexBufferFloat::log() {
   for (auto it : mDataVertices) {
      FLOG_INFO("Vertex written: %f", it);
   }
}

} /* core */
} /* fillwave */
