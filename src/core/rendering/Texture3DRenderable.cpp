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

#include <fillwave/core/rendering/Texture3DRenderable.h>
#include <fillwave/Log.h>

FLOGINIT("Texture3DRenderable", FERROR | FFATAL)

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
    : Texture3D(pX /*right*/ , nX /*left*/ , pY /*ceil*/ , nY /*floor*/ , pZ /*front*/ , nZ /*back*/ , params)
    , mShadowTexture(tex) {
  // nothing
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
  Framebuffer::bindScreenFramebuffer();
}

void Texture3DRenderable::setAttachmentFace(GLenum face, GLenum attachment) {
  mShadowTexture->attachTexture2DDraw(attachment, face, getHandle());
  fLogC("Setting Face framebuffer failed");
#ifdef FILLWAVE_BACKEND_OPENGL_ES_30
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
