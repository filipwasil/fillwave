/*
 * FramebufferGeometry.cpp
 *
 *  Created on: 22 May 2015
 *      Author: Filip Wasil
 */

#include <fillwave/core/rendering/FramebufferGeometry.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>

FLOGINIT("FramebufferGeometry", FERROR | FFATAL)

namespace fillwave {
namespace framework {
class TextureManager;
}
namespace core {

FramebufferGeometry::FramebufferGeometry(
		framework::TextureSystem* textures,
		GLuint width,
		GLuint height,
		GLuint colorBuffers,
		GLuint depthBuffers) :
			Framebuffer(1),
			mColorBufferSize(colorBuffers),
			mSummaryBufferSize(1),
			mDepthStencilBufferSize(depthBuffers),
			mSummaryBuffer(GL_COLOR_ATTACHMENT0 + colorBuffers),
			mNone(GL_NONE) {

	mDeferredColors = textures->getDeferredColor(width, height,
		mColorBufferSize);
	mStencilDepth = textures->getDeferredStencilDepth(width, height);
	mSummary = textures->getDeferredColorScreen(width, height);

	reload();
}

void FramebufferGeometry::resize(GLuint width, GLuint height) {
	for (GLint i = 0; i < mColorBufferSize; i++) {
		mDeferredColors->mFile->mHeader.mWidth = width;
		mDeferredColors->mFile->mHeader.mHeight = height;
		mDeferredColors->mFile->mData = nullptr;
		mDeferredColors->bind(i, i);
		mDeferredColors->sendData();
		mDeferredColors->unbind();
	}

	mSummary->mFile->mHeader.mWidth = width;
	mSummary->mFile->mHeader.mHeight = height;
	mSummary->mFile->mData = nullptr;
	mSummary->bind(mColorBufferSize, mColorBufferSize);
	mSummary->sendData();
	mSummary->unbind();

	mStencilDepth->mFile->mHeader.mWidth = width;
	mStencilDepth->mFile->mHeader.mHeight = height;
	mStencilDepth->mFile->mData = nullptr;
	mStencilDepth->bind(mColorBufferSize + mSummaryBufferSize, 0);
	mStencilDepth->sendData();
	mStencilDepth->unbind();
}

void FramebufferGeometry::bindAttachments() {
	for (int attachment = 0; attachment < mColorBufferSize; attachment++) {
		mDeferredColors->bind(attachment, attachment);
	}
}

void FramebufferGeometry::setAttachments() {
	//startFrame
	bindForWriting();
#ifdef FILLWAVE_GLES_3_0
	glDrawBuffers(1,&mSummaryBuffer);
#else
	glDrawBuffer(mSummaryBuffer);
#endif
	glClear(GL_COLOR_BUFFER_BIT);

	//BindForGeomPass
	glDrawBuffers(mColorBufferSize, mColorBuffers.data());
}

void FramebufferGeometry::setAttachmentStencilDepth() {
#ifdef FILLWAVE_GLES_3_0
	glDrawBuffers(1,&mNone);
#else
	glDrawBuffer(GL_NONE);
#endif
}

void FramebufferGeometry::setAttachmentSummaryForReading() {
	bindScreenFramebufferForWriting();
	bindForReading();
	glReadBuffer(mSummaryBuffer);
}

void FramebufferGeometry::setAttachmentSummaryForWriting() {
#ifdef FILLWAVE_GLES_3_0
	glDrawBuffers(1,&mSummaryBuffer);
#else
	glDrawBuffer(mSummaryBuffer);
#endif
}

void FramebufferGeometry::reload() {
	Framebuffer::reload();

	bindForWriting();

	for (GLint i = 0; i < mColorBufferSize; i++) {
		mDeferredColors->bind(i, i);
		attachTexture2DDraw(
		GL_COLOR_ATTACHMENT0 + i,
		GL_TEXTURE_2D, mDeferredColors->getHandle(i));
	}

	FLOG_CHECK("attachTexture2DDraw color failed");

	mSummary->bind(mColorBufferSize);
	attachTexture2DDraw(
	GL_COLOR_ATTACHMENT0 + mColorBufferSize,
	GL_TEXTURE_2D, mSummary->getHandle());

	mStencilDepth->bind();
	attachTexture2DDraw(
	GL_DEPTH_STENCIL_ATTACHMENT,
	GL_TEXTURE_2D, mStencilDepth->getHandle());

	for (GLint i = 0; i < mColorBufferSize + 1; i++) {
		mColorBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
	}

	mColorBuffers.push_back(GL_COLOR_ATTACHMENT0 + mColorBufferSize);

	glDrawBuffers(mColorBufferSize, mColorBuffers.data());

	bindScreenFramebufferForWriting();
}

} /* core */
} /* fillwave */
