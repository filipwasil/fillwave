/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/flc/extended/rendering/FramebufferGeometry.h>

namespace flw {
namespace flc {

FramebufferGeometry::FramebufferGeometry(flf::TextureSystem &textures,
    GLuint width,
    GLuint height,
    GLuint colorBuffers)
    : Framebuffer()
    , mColorBufferSize(colorBuffers)
    , mSummaryBufferSize(1)
    , mSummaryBuffer(GL_COLOR_ATTACHMENT0 + colorBuffers) {

  reload();
}

void FramebufferGeometry::resize(GLuint width, GLuint height) {
  for (GLint i = 0; i < mColorBufferSize; ++i) {
    mDeferredColors->mCfg->mHeader.mWidth = width;
    mDeferredColors->mCfg->mHeader.mHeight = height;
    mDeferredColors->mCfg->mData = nullptr;
    mDeferredColors->bind(i, i);
    mDeferredColors->sendData();
    mDeferredColors->unbind();
  }

  mSummary->mCfg->mHeader.mWidth = width;
  mSummary->mCfg->mHeader.mHeight = height;
  mSummary->mCfg->mData = nullptr;
  mSummary->bind(mColorBufferSize, mColorBufferSize);
  mSummary->sendData();
  mSummary->unbind();

  mStencilDepth->mCfg->mHeader.mWidth = width;
  mStencilDepth->mCfg->mHeader.mHeight = height;
  mStencilDepth->mCfg->mData = nullptr;
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
}

void FramebufferGeometry::setAttachmentStencilDepth() {

}

void FramebufferGeometry::setAttachmentSummaryForReading() {
  bindScreenFramebufferForWriting();
  bindForReading();
}

void FramebufferGeometry::setAttachmentSummaryForWriting() {

}

void FramebufferGeometry::reload() {
  Framebuffer::reload();

  bindForWriting();

  for (GLint i = 0; i < mColorBufferSize; ++i) {
    mDeferredColors->bind(i, i);
    attachTexture2DDraw(GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mDeferredColors->mTexture.mHandles[i]);
  }

  mSummary->bind(mColorBufferSize);
  attachTexture2DDraw(GL_COLOR_ATTACHMENT0 + mColorBufferSize, GL_TEXTURE_2D, mSummary->mTexture.mHandles[0]);

  mStencilDepth->bind();
  attachTexture2DDraw(GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mStencilDepth->mTexture.mHandles[0]);

  for (GLint i = 0; i < mColorBufferSize + 1; ++i) {
    mColorBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
  }

  mColorBuffers.push_back(GL_COLOR_ATTACHMENT0 + mColorBufferSize);

  bindScreenFramebufferForWriting();
}

} /* flc */
} /* flw */
