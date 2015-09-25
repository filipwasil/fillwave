/*
 * Texture3DRenderable.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: filip
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

#include <fillwave/core/rendering/Texture3DRenderable.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Texture3DRenderable", FERROR | FFATAL)

namespace fillwave {
namespace core {

Texture3DRenderable::Texture3DRenderable(
		Texture2DFile& filePosX,
		Texture2DFile& fileNegX,
		Texture2DFile& filePosY,
		Texture2DFile& fileNegY,
		Texture2DFile& filePosZ,
		Texture2DFile& fileNegZ,
		pTexture2DRenderable texture,
		ParameterList& parameters)
		: Texture3D(filePosX, //right
				fileNegX, //left
				filePosY, //ceil
				fileNegY, //floor
				filePosZ, //front
				fileNegZ, //back
				parameters), mShadowTexture(texture) {

}

Texture3DRenderable::~Texture3DRenderable() {

}

void Texture3DRenderable::resize(GLint width, GLint heigth) {
	mFront->mHeader.mWidth = width;
	mFront->mHeader.mHeight = heigth;
	mFront->mData = nullptr;

	mBack->mHeader.mWidth = width;
	mBack->mHeader.mHeight = heigth;
	mBack->mData = nullptr;

	mCeil->mHeader.mWidth = width;
	mCeil->mHeader.mHeight = heigth;
	mCeil->mData = nullptr;

	mFloor->mHeader.mWidth = width;
	mFloor->mHeader.mHeight = heigth;
	mFloor->mData = nullptr;

	mRight->mHeader.mWidth = width;
	mRight->mHeader.mHeight = heigth;
	mRight->mData = nullptr;

	mLeft->mHeader.mWidth = width;
	mLeft->mHeader.mHeight = heigth;
	mLeft->mData = nullptr;
	bind();
	sendData();
	unbind();
}

void Texture3DRenderable::bindForWriting() {
	mShadowTexture->bindForWriting();
}

void Texture3DRenderable::setAttachment(GLenum attachment) {
	bind();
	mShadowTexture->bindForRendering();
	mShadowTexture->setAttachment(attachment);
	FLOG_CHECK("Setting RGBA framebuffer failed");
	unbind();
	core::Framebuffer::bindScreenFramebuffer();
}

void Texture3DRenderable::setAttachmentFace(GLenum face, GLenum attachment) {
	mShadowTexture->attachTexture2DDraw(attachment, face, getHandle());
	FLOG_CHECK("Setting Face framebuffer failed");
#ifndef __ANDROID__
	glDrawBuffer(attachment);
#else
	GLenum target = attachment;
	glDrawBuffers(1,&target);
#endif
}

void Texture3DRenderable::log() {

}

} /* core */
} /* fillwave */
