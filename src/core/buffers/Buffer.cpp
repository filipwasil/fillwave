/*
 * Buffer.cpp
 *
 * Created on: 1 Mar 2013
 * Author: Filip Wasil
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

#include <fillwave/extras/Log.h>
#include <fillwave/core/buffers/Buffer.h>
#include <fillwave/core/pipeline/Attribute.h>

FLOGINIT("Buffer", FERROR | FFATAL)

using namespace std;

namespace fillwave {
namespace core {

Buffer::Buffer(GLuint target, GLuint drawType, GLuint index, GLsizei howMany)
		: GLObject(howMany), mRefresh(GL_TRUE), mIndex(index) {
	setTarget(target);
	setDrawType(drawType);
	reload();
}

Buffer::~Buffer() {
	glGenBuffers(mHowMany, mHandles);
}

void Buffer::setElements(GLuint elements) {
	mTotalElements = elements;
}
void Buffer::setSize(GLuint size) {
	mSize = size;
}

void Buffer::setTarget(GLuint target) {
	if (target == GL_ARRAY_BUFFER_BINDING || target == GL_ARRAY_BUFFER
			|| target == GL_ELEMENT_ARRAY_BUFFER || target == GL_UNIFORM_BUFFER
			|| target == GL_ELEMENT_ARRAY_BUFFER_BINDING
			|| target == GL_PIXEL_PACK_BUFFER) {
		mTarget = target;
	} else {
		FLOG_ERROR("Invalid target %d", mTarget);
	}
}

void Buffer::setDrawType(GLuint dataStoreType) {
	if (dataStoreType == GL_STREAM_DRAW || dataStoreType == GL_STREAM_READ
			|| dataStoreType == GL_STREAM_COPY || dataStoreType == GL_STATIC_DRAW
			|| dataStoreType == GL_STATIC_READ || dataStoreType == GL_STATIC_COPY
			|| dataStoreType == GL_DYNAMIC_DRAW || dataStoreType == GL_DYNAMIC_READ
			|| dataStoreType == GL_DYNAMIC_COPY) {
		mDataStoreType = dataStoreType;
	} else {
		FLOG_ERROR("Invalid data store type %d", mTarget);
	}
}

bool Buffer::isReady() {
	return mRefresh;
}

void Buffer::setReady() {
	mRefresh = GL_TRUE;
}

void Buffer::resetReady() {
	mRefresh = GL_FALSE;
}

GLuint Buffer::getElements() {
	return mTotalElements;
}

GLuint Buffer::getSize() {
	return mSize;
}

GLvoid* Buffer::getData() {
	return mData;
}

void Buffer::unmap() {
	glUnmapBuffer(mTarget);
	FLOG_CHECK("Could not unmap the buffer object");
}

void Buffer::bind(GLuint id) {
	glBindBuffer(mTarget, mHandles[id]);
	FLOG_CHECK("Could not bind the buffer object");
}

void Buffer::bindBase(GLuint id) {
	glBindBufferBase(mTarget, mIndex, mHandles[id]);
	FLOG_CHECK("Bind the uniform buffer object");
}

void Buffer::unbind() {
	glBindBuffer(mTarget, 0);
	FLOG_CHECK("Could not unbind the buffer object");
}

void Buffer::bind(GLuint externalTarget, GLuint id) {
	glBindBuffer(externalTarget, mHandles[id]);
	FLOG_CHECK("Could not bind the buffer object");
}

void Buffer::bindBase(GLuint externalTarget, GLuint id) {
	glBindBufferBase(externalTarget, mIndex, mHandles[id]);
	FLOG_CHECK("Bind the uniform buffer object");
}

void Buffer::unbindBase(GLuint externalTarget) {
	glBindBufferBase(externalTarget, mIndex, 0);
	FLOG_CHECK("Could not unbind the buffer object");
}

void Buffer::send() {
	if (mRefresh) {
		glBufferData(mTarget, mSize, mData, mDataStoreType);
		mRefresh = GL_FALSE;
		FLOG_CHECK("Could not send the data");
	}
}

GLvoid* Buffer::mapRange(GLenum access, GLuint size) {
	GLvoid* ptr = nullptr;
	if (size) {
		ptr = glMapBufferRange(mTarget, 0, size, access);
		FLOG_CHECK("Could not map range of the buffer object");
	} else {
		ptr = glMapBufferRange(mTarget, 0, mSize, access);
		FLOG_CHECK("Could not map range of the buffer object");
	}
	return ptr;
}

void Buffer::reload() {
	glGenBuffers(mHowMany, mHandles);
	FLOG_CHECK("reload");
}

/* Feature not available in OpenGL ES  <= 3.0 */
#ifdef __ANDROID__
#else
GLvoid* Buffer::map(GLenum access) {
	GLvoid* ptr = glMapBuffer(mTarget, access);
	FLOG_CHECK("Could not map the buffer object");
	return ptr;
}
#endif

} /* core */
} /* fillwave */
