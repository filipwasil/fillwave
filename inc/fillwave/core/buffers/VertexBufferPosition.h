/*
 * VertexBufferPosition.h
 *
 *  Created on: Dec 7, 2014
 *      Author: Filip Wasil
 */

#ifndef VertexBufferPosition_H_
#define VertexBufferPosition_H_

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

/*! \struct VertexPosition
 * \brief Not used. Stores the position vertex data.
 */

struct VertexPosition {
	GLfloat mPosition[4];
};

/*! \class VertexBufferPosition
 * \brief Not used. Vertex buffer specialized with VertexPosition data structure.
 */

class VertexBufferPosition: public VertexBuffer<VertexPosition> {
public:
	VertexBufferPosition(
			models::Shape<VertexPosition>& shape,
			GLuint dataStoreModification = GL_STATIC_DRAW);
	VertexBufferPosition(
			std::vector<VertexPosition>& vertices,
			GLuint dataStoreModification = GL_STATIC_DRAW);
	virtual ~VertexBufferPosition();
	void log();
};

} /* core */
typedef std::shared_ptr<core::VertexBufferPosition> pVertexBufferPosition;
typedef std::unique_ptr<core::VertexBufferPosition> puVertexBufferPosition;
} /* fillwave*/

#endif /* VertexBufferPosition_H_ */
