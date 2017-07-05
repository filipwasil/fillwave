/*
 * Texture3DRenderable.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
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


#include <fillwave/core/rendering/Texture3DRenderable.h>
#include <fillwave/Log.h>

FLOGINIT("Texture3DRenderable", FERROR | FFATAL)

namespace flw {
namespace flc {

Texture3DRenderable::Texture3DRenderable(flc::Texture2DFile *filePosX,
    flc::Texture2DFile *fileNegX,
    flc::Texture2DFile *filePosY,
    flc::Texture2DFile *fileNegY,
    flc::Texture2DFile *filePosZ,
    flc::Texture2DFile *fileNegZ,
    flc::Texture2DRenderable *texture,
    ParameterList &parameters)
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
  fLogC("Setting RGBA framebuffer failed");
  unbind();
  flc::Framebuffer::bindScreenFramebuffer();
}

void Texture3DRenderable::setAttachmentFace(GLenum face, GLenum attachment) {
  mShadowTexture->attachTexture2DDraw(attachment, face, getHandle());
  fLogC("Setting Face framebuffer failed");
#ifdef FILLWAVE_GLES_3_0
  GLenum target = attachment;
  glDrawBuffers(1, &target);
#else
  glDrawBuffer(attachment);
#endif
}

void Texture3DRenderable::log() {

}

} /* flc */
} /* flw */
