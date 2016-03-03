/*
 * UniformBuffer.cpp
 *
 *  Created on: May 18, 2014
 *      Author: filip
 */

#include <fillwave/core/pipeline/UniformBuffer.h>
#include <fillwave/Log.h>

FLOGINIT("UniformBuffer", FERROR | FFATAL)

namespace fillwave {
namespace core {

UniformBuffer::UniformBuffer(
		std::string name,
		GLuint index,
		GLuint uniformBlockSize,
		GLuint bindingPoint,
		GLuint dataStoreModification) :
			Buffer(GL_UNIFORM_BUFFER, dataStoreModification, index),
			mName(name),
			mBindingPoint(bindingPoint) {
	bind();
	bindBase();
	unbind();
	mSize = uniformBlockSize;

}

UniformBuffer::~UniformBuffer() {

}

void UniformBuffer::bindRange(GLuint id) {
	return glBindBufferRange(mTarget, mBindingPoint, mHandles[id], 0, mSize);
}

void UniformBuffer::push(GLfloat* data) {
	bind();
	mData = data;
	send();
	mRefresh = GL_TRUE; //xxx always refresh
	unbind();
}

std::string UniformBuffer::getName() {
	return mName;
}

} /* core */
} /* fillwave */
