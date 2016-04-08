/*
 * Texture2D.cpp
 *
 *  Created on: 28 Mar 2014
 *      Author: Filip Wasil
 */

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/Log.h>

FLOGINIT("Texture2D", FERROR | FFATAL | FDEBUG)

namespace fillwave {
namespace core {

Texture2D::Texture2D(
    Texture2DFile* file,
    ParameterList& parameters,
    GLuint howMany) :
	Texture(GL_TEXTURE_2D, howMany),
	mFile(puTexture2DFile(file)),
	mParameters(parameters) {
	reload();
}

void Texture2D::sendData(Texture2DFileData data) {
	if (data) {
		mFile->mData = data;
	}
	if (mFile->mConfig.mCompression) {
		glCompressedTexImage2D(mTarget, mFile->mConfig.mMipmapsLevel,
		                       mFile->mHeader.mInternalFormat, mFile->mHeader.mWidth,
		                       mFile->mHeader.mHeight, mFile->mConfig.mBorder,
		                       mFile->mConfig.mCompressionSize, (GLubyte*) mFile->mData);
	} else {
		glTexImage2D(mTarget, mFile->mConfig.mMipmapsLevel,
		             mFile->mHeader.mInternalFormat, mFile->mHeader.mWidth,
		             mFile->mHeader.mHeight, mFile->mConfig.mBorder, mFile->mHeader.mFormat,
		             mFile->mHeader.mType, (GLubyte*) mFile->mData);
	}
	FLOG_CHECK("send data");
}

void Texture2D::generateMipMaps() {
	if (mFile->mConfig.mMipmaps) {
		glGenerateMipmap(mTarget);
		FLOG_CHECK("generateMipMaps");
	}
}

void Texture2D::unbind2DTexture(GLint textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::unbind2DTextures() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::reload() {
	FLOG_DEBUG("Reload");
	Texture::reload();
	for (GLsizei i = 0; i < mHowMany; i++) {
		bind(i);
		setParameters(mParameters);
		sendData();
		generateMipMaps();
//      unbind();
	}
}

void Texture2D::log() {
	FLOG_DEBUG("mTarget: 0x%x", mTarget);
	FLOG_DEBUG("mFile->mConfig.mMipmapsLevel: %d", mFile->mConfig.mMipmapsLevel);
	FLOG_DEBUG("mFile->mHeader.mInternalFormat: 0x%x",
	           mFile->mHeader.mInternalFormat);
	FLOG_DEBUG("mFile->mHeader.mWidth: %d", mFile->mHeader.mWidth);
	FLOG_DEBUG("mFile->mHeader.mHeight: %d", mFile->mHeader.mHeight);
	FLOG_DEBUG("mFile->mConfig.mBorder: %d", mFile->mConfig.mBorder);
	FLOG_DEBUG("mFile->mConfig.mType: 0x%x", mFile->mHeader.mType);
	FLOG_DEBUG("mFile->mHeader.mFormat: 0x%x", mFile->mHeader.mFormat);
}

} /* core */
} /* fillwave */
