/*
 * VertexArray.cpp
 *
 *  Created on: 4 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/Log.h>

#include <fillwave/core/buffers/VertexArray.h>

FLOGINIT("VertexArray", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexArray::VertexArray(GLuint howMany) :
	GLObject(howMany) {
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

void VertexArray::unbindVAO() {
	glBindVertexArray(0);
	FLOG_CHECK("ould unbind the VAO");
}

void VertexArray::reload() {
	glGenVertexArrays(mHowMany, mHandles);
	FLOG_CHECK("reload");
}

void bindVAO(GLuint handle) {
	glBindVertexArray(handle);
	FLOG_CHECK("Could not bind the VAO");
}

} /* core */
} /* Fillwave */
