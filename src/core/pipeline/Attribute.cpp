/*
 * Attribute.cpp
 *
 *  Created on: 2 Mar 2014
 *      Author: Filip Wasil
 */

#include <fillwave/core/pipeline/Attribute.h>

#include <fillwave/extras/Log.h>

FLOGINIT("Attribute", FERROR | FFATAL)

namespace fillwave {
namespace core {

Attribute::Attribute(
		std::string name,
		GLuint index,
		GLint size,
		GLsizei stride,
		GLenum type,
		GLboolean normalized)
		:
				mStride(stride),
				mName(name),
				mIndex(index),
				mSize(size),
				mNormalized(normalized),
				mType(type),
				mPointer((GLvoid*) 0) {

	switch (mType) {
		case GL_UNSIGNED_INT:
		case GL_UNSIGNED_INT_VEC2:
		case GL_UNSIGNED_INT_VEC3:
		case GL_UNSIGNED_INT_VEC4:
			//mType = GL_UNSIGNED_SHORT;
			mTypeSize = sizeof(GLuint);
			break;
		case GL_FLOAT:
		case GL_FLOAT_VEC2:
		case GL_FLOAT_VEC3:
		case GL_FLOAT_VEC4:
		case GL_FLOAT_MAT2:
		case GL_FLOAT_MAT3:
		case GL_FLOAT_MAT4:
			mTypeSize = sizeof(GLfloat);
			break;
		case GL_INT:
		case GL_INT_VEC2:
		case GL_INT_VEC3:
		case GL_INT_VEC4:
			//mType = GL_SHORT;
			mTypeSize = sizeof(GLint);
			break;
		case GL_BOOL:
		case GL_BOOL_VEC2:
		case GL_BOOL_VEC3:
		case GL_BOOL_VEC4:
			mTypeSize = sizeof(GLboolean);
			break;
		default:
			std::cout << "Not supported type of attribute" << std::endl;
			mTypeSize = sizeof(float);
			break;
	}
}

void Attribute::bindLocation(GLint programHandle) {
	glBindAttribLocation(programHandle, mIndex, mName.c_str());
	FLOG_CHECK("bindAttribLocation");
}

void Attribute::arrayDisable() {
	glDisableVertexAttribArray(mIndex);
	FLOG_CHECK("disableAttribLocation");
}

void Attribute::arrayEnable() {
	glEnableVertexAttribArray(mIndex);
	FLOG_CHECK("enableAttribLocation");
}

void Attribute::arraySet() {
	glVertexAttribPointer(mIndex, mSize,
//                          mType,
			GL_FLOAT, mNormalized, mStride, mPointer);
	FLOG_CHECK("VertexAttribPointer");
}

void Attribute::setOffsetPointer(GLvoid* offset) {
	mPointer = offset;
}

GLuint Attribute::getSize() {
	return mSize;
}

std::size_t Attribute::getTypeSize() {
	return mTypeSize;
}

GLuint Attribute::getIndex() {
	return mIndex;
}

std::string Attribute::getName() {
	return mName;
}

void Attribute::log() {
	FLOG_INFO("mName %s", mName.c_str());
	FLOG_INFO("mType 0x%x", mType);
	FLOG_INFO("mIndex %d", mIndex);
	FLOG_INFO("mSize %d", mSize);
	FLOG_INFO("mType%d ", mType);
	FLOG_INFO("mNormalized %d", mNormalized);
	FLOG_INFO("mStride %d", mStride);
}

} /* core */
} /* fillwave */
