/*
 * VertexBufferText.h
 *
 *  Created on: Jul 26, 2014
 *      Author: Filip Wasil
 */

#ifndef VERTEXBUFFERTEXT_H_
#define VERTEXBUFFERTEXT_H_

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

/*! \struct VertexText
 * \brief Stores the text vertex data.
 */

struct VertexText {
	float position[2];
	float uv[2];
};

/*! \class VertexBufferText
 * \brief Vertex buffer specialized with VertexText data structure.
 */

class VertexBufferText: public VertexBuffer<VertexText> {
public:
	VertexBufferText(
			std::vector<GLfloat> data,
			std::vector<GLfloat> textureCoords,
			GLuint dataStoreModification = GL_DYNAMIC_DRAW);
	virtual ~VertexBufferText();
	void log();
};

} /* core */
typedef std::shared_ptr<core::VertexBufferText> pVertexBufferText;
} /* fillwave */

#endif /* VERTEXBUFFERTEXT_H_ */
