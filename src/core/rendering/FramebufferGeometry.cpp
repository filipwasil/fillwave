/*
 * FramebufferGeometry.cpp
 *
 *  Created on: 22 May 2015
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


#include <fillwave/core/rendering/FramebufferGeometry.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>

FLOGINIT("FramebufferGeometry", FERROR | FFATAL)

namespace flw {
namespace flf {
class TextureManager;
}
namespace flc {

FramebufferGeometry::FramebufferGeometry(flf::TextureSystem *textures,
    GLuint width,
    GLuint height,
    GLuint colorBuffers,
    GLuint depthBuffers)
    : Framebuffer(1), mColorBufferSize(colorBuffers), mSummaryBufferSize(1), mDepthStencilBufferSize(depthBuffers)
    , mSummaryBuffer(GL_COLOR_ATTACHMENT0 + colorBuffers), mNone(GL_NONE) {

  mDeferredColors = textures->getDeferredColor(width, height, mColorBufferSize);
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
  glDrawBuffers(1, &mSummaryBuffer);
#else
  glDrawBuffer(mSummaryBuffer);
#endif
  glClear(GL_COLOR_BUFFER_BIT);

  //BindForGeomPass
  glDrawBuffers(mColorBufferSize, mColorBuffers.data());
}

void FramebufferGeometry::setAttachmentStencilDepth() {
#ifdef FILLWAVE_GLES_3_0
  glDrawBuffers(1, &mNone);
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
  glDrawBuffers(1, &mSummaryBuffer);
#else
  glDrawBuffer(mSummaryBuffer);
#endif
}

void FramebufferGeometry::reload() {
  Framebuffer::reload();

  bindForWriting();

  for (GLint i = 0; i < mColorBufferSize; i++) {
    mDeferredColors->bind(i, i);
    attachTexture2DDraw(GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mDeferredColors->getHandle(i));
  }

  fLogC("attachTexture2DDraw color failed");

  mSummary->bind(mColorBufferSize);
  attachTexture2DDraw(GL_COLOR_ATTACHMENT0 + mColorBufferSize, GL_TEXTURE_2D, mSummary->getHandle());

  mStencilDepth->bind();
  attachTexture2DDraw(GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mStencilDepth->getHandle());

  for (GLint i = 0; i < mColorBufferSize + 1; i++) {
    mColorBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
  }

  mColorBuffers.push_back(GL_COLOR_ATTACHMENT0 + mColorBufferSize);

  glDrawBuffers(mColorBufferSize, mColorBuffers.data());

  bindScreenFramebufferForWriting();
}

} /* flc */
} /* flw */
