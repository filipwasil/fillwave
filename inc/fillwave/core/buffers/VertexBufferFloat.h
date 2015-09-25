/*
 * VertexBufferFloat.h
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

#ifndef SRC_CORE_BUFFERS_VERTEXBUFFERFLOAT_H_
#define SRC_CORE_BUFFERS_VERTEXBUFFERFLOAT_H_

#include <fillwave/core/buffers/VertexBuffer.h>

namespace fillwave {
namespace core {

/*! \class VertexBufferPosition
 * \brief Vertex buffer specialized with GLfloat data structure.
 */

class VertexBufferFloat: public VertexBuffer<GLfloat> {
public:
   VertexBufferFloat(std::vector<GLfloat>& values,
                     GLuint dataStoreModification = GL_STATIC_DRAW);
   virtual ~VertexBufferFloat();
   void log();
};

} /* core */
typedef std::shared_ptr<core::VertexBufferFloat> pVertexBufferFloat;
} /* fillwave */

#endif /* SRC_CORE_BUFFERS_VERTEXBUFFERFLOAT_H_ */
