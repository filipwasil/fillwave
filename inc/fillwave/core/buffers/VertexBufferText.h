/*
 * VertexBufferText.h
 *
 *  Created on: Jul 26, 2014
 *      Author: Filip Wasil
 */

#ifndef VERTEXBUFFERTEXT_H_
#define VERTEXBUFFERTEXT_H_

#include <fillwave/core/buffers/TVertexBuffer.h>

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

class VertexBufferText: public TVertexBuffer<VertexText> {
 public:
	VertexBufferText(
	   std::vector<GLfloat> data,
	   std::vector<GLfloat> textureCoords,
	   GLuint dataStoreModification = GL_DYNAMIC_DRAW);
	virtual ~VertexBufferText() = default;
	void log() const;
};

} /* core */
typedef std::shared_ptr<core::VertexBufferText> pVertexBufferText;
} /* fillwave */

#endif /* VERTEXBUFFERTEXT_H_ */
