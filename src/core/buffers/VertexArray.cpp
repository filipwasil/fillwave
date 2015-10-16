/*
 * VertexArray.cpp
 *
 *  Created on: 4 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/extras/Log.h>

#include <fillwave/core/buffers/VertexArray.h>

FLOGINIT("VertexArray", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexArray::VertexArray(GLuint howMany)
		: GLObject(howMany) {
	glGenVertexArrays(mHowMany, mHandles);
	FLOG_CHECK("Could not generate the VAO");
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(mHowMany, mHandles);
	FLOG_CHECK("Could not delete the VAO");
}

void VertexArray::bind(GLuint id) {
	glBindVertexArray(mHandles[id]);
	FLOG_CHECK("Could not bind the VAO");
}

void VertexArray::unbind() {
	glBindVertexArray(0);
	FLOG_CHECK("ould unbind the VAO");
}

void VertexArray::reload() {
	glGenVertexArrays(mHowMany, mHandles);
	FLOG_CHECK("reload");
}

} /* core */
} /* Fillwave */
