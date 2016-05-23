/*
 * Texture.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fillwave/core/texturing/Texture.h>
#include <fillwave/Log.h>

FLOGINIT("Texture", FERROR | FFATAL | FDEBUG)

namespace fillwave {
namespace core {

Texture2DFileConfig::Texture2DFileConfig(
   GLint level,
   GLint border,
   GLboolean mipmaps,
   GLboolean compression) :
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
   GLsizei height) :
	mInternalFormat(internalFormat),
	mHeight(height),
	mWidth(width),
	mType(type),
	mFormat(format) {

}

Texture::Texture(GLenum textureTarget, GLsizei howMany) :
	GLObject(howMany), mTarget(textureTarget) {
	reload();
}

Texture::~Texture() {
	glDeleteTextures(mHowMany, mHandles);
	FLOG_CHECK("Could not delete texture");
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

void bindTexture(GLuint target, GLuint handle) {
	glBindTexture(target, handle);
	FLOG_CHECK("bind (id) texture");
}

void bindTexture(GLint textureUnit, GLuint target, GLuint handle) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(target, handle);
	FLOG_CHECK("bind (texUnit, id) texture");
}

void unbindTexture(GLuint target) {
	glBindTexture(target, 0);
	FLOG_CHECK("unbind texture");
}

} /* core  */
} /* fillwave */
