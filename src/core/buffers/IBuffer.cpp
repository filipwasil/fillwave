/*
 * Buffer.cpp
 *
 * Created on: 1 Mar 2013
 * Author: Filip Wasil
 */

#include <fillwave/core/buffers/IBuffer.h>
#include <fillwave/Log.h>
#include <fillwave/core/pipeline/Attribute.h>

FLOGINIT("Buffer", FERROR | FFATAL)

using namespace std;

namespace fillwave {
namespace core {

IBuffer::IBuffer(GLuint target, GLuint drawType, GLuint index, GLsizei howMany) :
	GLObject(howMany), mLoaded(GL_FALSE), mIndex(index) {
	setTarget(target);
	setDrawType(drawType);
	reload();
}

IBuffer::~IBuffer() {
	glDeleteBuffers(mHowMany, mHandles);
}

void IBuffer::setElements(GLuint elements) {
	mTotalElements = elements;
}
void IBuffer::setSize(GLuint size) {
	mSize = size;
}

void IBuffer::setTarget(GLuint target) {
	if (target == GL_ARRAY_BUFFER_BINDING || target == GL_ARRAY_BUFFER
	      || target == GL_ELEMENT_ARRAY_BUFFER || target == GL_UNIFORM_BUFFER
	      || target == GL_ELEMENT_ARRAY_BUFFER_BINDING
	      || target == GL_PIXEL_PACK_BUFFER) {
		mTarget = target;
	} else {
		FLOG_ERROR("Invalid target %d", mTarget);
	}
}

void IBuffer::setDrawType(GLuint dataStoreType) {
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

bool IBuffer::isLoaded() {
	return mLoaded;
}

void IBuffer::setLoaded(GLboolean loaded) {
    mLoaded = loaded;
}

GLuint IBuffer::getElements() const {
	return mTotalElements;
}

GLuint IBuffer::getSize() const {
	return mSize;
}

GLvoid* IBuffer::getData() const {
	return mData;
}

void IBuffer::unmap() const {
	glUnmapBuffer(mTarget);
	FLOG_CHECK("Could not unmap the buffer object");
}

void IBuffer::bind(GLuint id) const {
	glBindBuffer(mTarget, mHandles[id]);
	FLOG_CHECK("Could not bind the buffer object");
}

void IBuffer::bindBase(GLuint id) const {
	glBindBufferBase(mTarget, mIndex, mHandles[id]);
	FLOG_CHECK("Bind the uniform buffer object");
}

void IBuffer::unbind() {
	glBindBuffer(mTarget, 0);
	FLOG_CHECK("Could not unbind the buffer object");
}

void IBuffer::bind(GLuint externalTarget, GLuint id) const {
	glBindBuffer(externalTarget, mHandles[id]);
	FLOG_CHECK("Could not bind the buffer object");
}

void IBuffer::bindBase(GLuint externalTarget, GLuint id) const {
	glBindBufferBase(externalTarget, mIndex, mHandles[id]);
	FLOG_CHECK("Bind the uniform buffer object");
}

void IBuffer::unbindBase(GLuint externalTarget) {
	glBindBufferBase(externalTarget, mIndex, 0);
	FLOG_CHECK("Could not unbind the buffer object");
}

void IBuffer::send() {
	if (!mLoaded) {
		glBufferData(mTarget, mSize, mData, mDataStoreType);
		mLoaded = GL_TRUE;
		FLOG_CHECK("Could not send the data");
	}
}

GLvoid* IBuffer::mapRange(GLenum access, GLuint size) {
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

void IBuffer::reload() {
	glGenBuffers(mHowMany, mHandles);
	FLOG_CHECK("reload");
}

/* Feature not available in OpenGL ES  < 3.1 */
#ifdef FILLWAVE_GLES_3_0
#else
GLvoid* IBuffer::map(GLenum access) const {
	GLvoid* ptr = glMapBuffer(mTarget, access);
	FLOG_CHECK("Could not map the buffer object");
	return ptr;
}
#endif

void unbindBuffer(GLuint target) {
	glBindBuffer(target, 0);
	FLOG_CHECK("Could not unbind the buffer object");
}

void bindBuffer(GLuint target, GLuint handle) {
	glBindBuffer(target, handle);
	FLOG_CHECK("Could not bind the buffer object");
}

} /* core */
} /* fillwave */
