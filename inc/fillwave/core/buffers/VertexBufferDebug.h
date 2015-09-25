/*
 * VertexBufferDebug.h
 *
 *  Created on: Aug 9, 2014
 *      Author: Filip Wasil
 */

#ifndef VERTEXBUFFERDEBUG_H_
#define VERTEXBUFFERDEBUG_H_

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

#include <fillwave/core/buffers/VertexBuffer.h>

namespace fillwave {
namespace core {

/*! \struct VertexDebug
 * \brief Stores the debugger vertex data.
 */

struct VertexDebug{
   float position[2];
   float uv[2];
};

/*! \class VertexBufferDebug
 * \brief Vertex buffer specialized with VertexDebug data structure.
 */

class VertexBufferDebug: public VertexBuffer<VertexDebug> {

public:
   VertexBufferDebug(GLfloat scale = 1.0);
   virtual ~VertexBufferDebug();
   void log();
};

} /* core */
typedef std::shared_ptr<core::VertexBufferDebug> pVertexBufferDebug;
} /* fillwave */

#endif /* VERTEXBUFFERDEBUG_H_ */
