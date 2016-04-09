/*
 * Texture.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
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
