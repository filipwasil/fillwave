/*
 * Texture.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
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
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/texturing/Texture.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Texture", FERROR | FFATAL | FDEBUG)

namespace fillwave {
namespace core {

Texture2DFileConfig::Texture2DFileConfig(
		GLint level,
		GLint border,
		GLboolean mipmaps,
		GLboolean compression)
		:
				mMipmapsLevel(level),
				mMipmaps(mipmaps),
				mCompression(compression),
				mBorder(border),
				mCompressionSize(0) {

}

Texture2DFileHeader::Texture2DFileHeader(
		GLint internalFormat,
		GLint format,
		GLint type,
		GLsizei width,
		GLsizei height)
		:
				mInternalFormat(internalFormat),
				mHeight(height),
				mWidth(width),
				mType(type),
				mFormat(format) {

}

Texture::Texture(GLenum textureTarget, GLsizei howMany)
		: GLObject(howMany), mTarget(textureTarget), mMapType(0) { //xxx why this has to be in generic texture class
	reload();
}

Texture::~Texture() {
	glDeleteTextures(mHowMany, mHandles);
	FLOG_CHECK("Could not delete texture");
}

GLuint Texture::getMapType() {
	return mMapType;
}

void Texture::setMapType(GLuint mapType) {
	mMapType = mapType;
}

GLint Texture::getTarget() {
	return mTarget;
}

void Texture::bind(GLuint id) {
	glBindTexture(mTarget, mHandles[id]);
	FLOG_CHECK("bind (id) texture");
}

void Texture::bind(GLint textureUnit, GLuint id) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(mTarget, mHandles[id]);
	FLOG_CHECK("bind (texUnit, id) texture");
}

void Texture::unbind() {
	glBindTexture(mTarget, 0);
	FLOG_CHECK("unbind texture");
}

void Texture::setParameter(GLenum parameter, GLenum value) {
	glTexParameteri(mTarget, parameter, value);
	FLOG_CHECK("setParameter");
}

void Texture::setParameters(ParameterList parameters) {
	for (auto it : parameters) {
		setParameter(it.first, it.second);
	}
}

void Texture::reload() {
	FLOG_DEBUG("Reload");
	glGenTextures(mHowMany, mHandles);
	FLOG_CHECK("glGenTextures");
}

} /* core  */
} /* fillwave */
