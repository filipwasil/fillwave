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

#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/Log.h>

FLOGINIT("Texture2DRenderable", FERROR | FFATAL | FDEBUG)

namespace flw {
namespace flc {

Texture2DRenderable::Texture2DRenderable(GLenum attachment, flc::TextureConfig* cfg, ParameterList& param)
    : Texture2D(cfg, param)
    , mFramebuffer()
    , mAttachment(attachment) {
  setAttachment(attachment);
}

void Texture2DRenderable::resize(GLint width, GLint heigth) {
  mCfg->mHeader.mWidth = width;
  mCfg->mHeader.mHeight = heigth;
  mCfg->mData = nullptr;
  bind();
  sendData();
  unbind();
}

void Texture2DRenderable::bindForWriting() {
  mFramebuffer.bindForWriting();
}

void Texture2DRenderable::bindForRendering() {
  mFramebuffer.bind();
}

void Texture2DRenderable::bindForReading() {
  mFramebuffer.bindForReading();
}

void Texture2DRenderable::setAttachment(GLenum attachment, GLenum target) {
  const GLenum none = GL_NONE;
  switch (attachment) {
    case GL_DEPTH_STENCIL_ATTACHMENT:
      bind();
      bindForRendering();
      mFramebuffer.attachTexture2D(GL_DEPTH_STENCIL_ATTACHMENT, target, getHandle());
      fLogC("Setting depth framebuffer failed");
      Framebuffer::bindScreenFramebuffer();
      break;
    case GL_DEPTH_ATTACHMENT:
      bind();
      bindForRendering();
      mFramebuffer.attachTexture2D(GL_DEPTH_ATTACHMENT, target, getHandle());
#ifdef FILLWAVE_GLES_3_0
    glDrawBuffers(1, &none);
    glReadBuffer(none); //xxx this does not have to be here
#else
      glDrawBuffer(none);
      glReadBuffer(none); //xxx this does not have to be here
#endif
      fLogC("Setting depth framebuffer failed");
      Framebuffer::bindScreenFramebuffer();
      break;
    case GL_COLOR_ATTACHMENT0:
      bind();
      bindForRendering();
      mFramebuffer.attachTexture2D(GL_COLOR_ATTACHMENT0, target, getHandle());
      fLogC("Setting RGBA framebuffer failed");
      unbind();
      Framebuffer::bindScreenFramebuffer();
      break;
  }
}

void Texture2DRenderable::attachTexture2DDraw(GLenum attachment, GLenum target, GLuint textureHandle) {
  mFramebuffer.attachTexture2DDraw(attachment, target, textureHandle);
}

void Texture2DRenderable::attachTexture2D(GLenum attachment, GLenum target, GLuint textureHandle) {
  mFramebuffer.attachTexture2D(attachment, target, textureHandle);
}

void Texture2DRenderable::copyTo(Framebuffer *source) {
  source->bindForWriting();
  /* We will bind framebufferuffer for reading ...*/
  mFramebuffer.bindForReading();
  /* .. and take color attachment color 0 ... */
  mFramebuffer.setReadColorAttachment(0);
  /* ... to finally copy it into main framebuffer */
  glBlitFramebuffer(0, 0, mCfg->mHeader.mWidth, mCfg->mHeader.mHeight, 0, 0, mCfg->mHeader.mWidth, mCfg->mHeader.mHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void Texture2DRenderable::copyFrom(Framebuffer *source) {
  mFramebuffer.bindForWriting();
  source->bindForReading();
  source->setReadColorAttachment(0);
  glBlitFramebuffer(0,
                    0,
                    mCfg->mHeader.mWidth,
                    mCfg->mHeader.mHeight,
                    0,
                    0,
                    mCfg->mHeader.mWidth,
                    mCfg->mHeader.mHeight,
                    GL_COLOR_BUFFER_BIT,
                    GL_LINEAR); /* ... to finally copy it into main framebuffer */
}

void Texture2DRenderable::log() {
  // nothing
}

void Texture2DRenderable::reload() {
  Texture2D::reload();
  mFramebuffer.reload();
  setAttachment(mAttachment);
}

} /* flc */
} /* flw */
