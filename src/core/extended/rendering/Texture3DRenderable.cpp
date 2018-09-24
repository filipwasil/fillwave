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

#include <fillwave/core/extended/rendering/Texture3DRenderable.h>
#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flc {

Texture3DRenderable::Texture3DRenderable(
  TextureConfig* pX
  , TextureConfig* nX
  , TextureConfig* pY
  , TextureConfig* nY
  , TextureConfig* pZ
  , TextureConfig* nZ
  , Texture2DRenderable* tex
  , ParameterList& params)
    : mTexture3D(pX /*right*/ , nX /*left*/ , pY /*ceil*/ , nY /*floor*/ , pZ /*front*/ , nZ /*back*/ , params)
    , mShadowTexture(tex) {
  // nothing
}

void Texture3DRenderable::resize(GLint width, GLint heigth) {
  mTexture3D.mFront->mHeader.mWidth = width;
  mTexture3D.mFront->mHeader.mHeight = heigth;
  mTexture3D.mFront->mData = nullptr;

  mTexture3D.mBack->mHeader.mWidth = width;
  mTexture3D.mBack->mHeader.mHeight = heigth;
  mTexture3D.mBack->mData = nullptr;

  mTexture3D.mCeil->mHeader.mWidth = width;
  mTexture3D.mCeil->mHeader.mHeight = heigth;
  mTexture3D.mCeil->mData = nullptr;

  mTexture3D.mFloor->mHeader.mWidth = width;
  mTexture3D.mFloor->mHeader.mHeight = heigth;
  mTexture3D.mFloor->mData = nullptr;

  mTexture3D.mRight->mHeader.mWidth = width;
  mTexture3D.mRight->mHeader.mHeight = heigth;
  mTexture3D.mRight->mData = nullptr;

  mTexture3D.mLeft->mHeader.mWidth = width;
  mTexture3D.mLeft->mHeader.mHeight = heigth;
  mTexture3D.mLeft->mData = nullptr;

  mTexture3D.bind();
  mTexture3D.sendData();
  mTexture3D.unbind();
}

void Texture3DRenderable::bindForWriting() {
  mShadowTexture->bindForWriting();
}

void Texture3DRenderable::setAttachment(GLenum attachment) {
  mTexture3D.bind();
  mShadowTexture->bindForRendering();
  mShadowTexture->setAttachment(attachment);
  fLogC("Setting RGBA framebuffer failed");
  mTexture3D.unbind();
  Framebuffer::bindScreenFramebuffer();
}

void Texture3DRenderable::setAttachmentFace(GLenum face, GLenum attachment) {
  mShadowTexture->attachTexture2DDraw(attachment, face, mTexture3D.mTexture.getHandle());
  fLogC("Setting Face framebuffer failed");
#if defined(FILLWAVE_BACKEND_OPENGL_ES_30)
  GLenum target = attachment;
  glDrawBuffers(1, &target);
#else
  glDrawBuffer(attachment);
#endif
}

void Texture3DRenderable::log() {
  // nothing
}

} /* flc */
} /* flw */
