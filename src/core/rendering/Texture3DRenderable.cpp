/*
 * Texture3DRenderable.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: filip
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
#ifdef FILLWAVE_GLES_3_0
	GLenum target = attachment;
	glDrawBuffers(1,&target);
#else
	glDrawBuffer(attachment);
#endif
}

void Texture3DRenderable::log() {

}

} /* core */
} /* fillwave */
