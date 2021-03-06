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

#include <flw/flc/rendering/Texture2DRenderable.h>
#include <flw/cmn/TextureConfigs.h>
#include <flw/Log.h>

FLOGINIT_DEFAULT()

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#define glBlitFramebuffer glBlitFramebufferNV
#else
#endif

namespace flw {
namespace flc {

Texture2DRenderable::Texture2DRenderable(GLenum attachment, flc::TextureConfig* cfg, ParameterList& param)
  : mTexture2D(cfg, param)
  , mFramebuffer()
  , mAttachment(attachment) {
  setAttachment(attachment);
}

void Texture2DRenderable::resize(GLint width, GLint heigth) {
  mTexture2D.mCfg->mHeader.mWidth = width;
  mTexture2D.mCfg->mHeader.mHeight = heigth;
  mTexture2D.mCfg->mData = nullptr;
  mTexture2D.bind();
  mTexture2D.sendData();
  mTexture2D.unbind();
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
  switch (attachment) {
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
    case GL_DEPTH_STENCIL_ATTACHMENT:
      mTexture2D.bind();
      bindForRendering();
      mFramebuffer.attachTexture2D(GL_DEPTH_STENCIL_ATTACHMENT, target, mTexture2D.mTexture.getHandle());
      fLogC("Setting depth framebuffer failed");
      Framebuffer::bindScreenFramebuffer();
      break;
#endif
    case GL_DEPTH_ATTACHMENT:
      mTexture2D.bind();
      bindForRendering();
      mFramebuffer.attachTexture2D(GL_DEPTH_ATTACHMENT, target, mTexture2D.mTexture.getHandle());
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#elif defined(FILLWAVE_BACKEND_OPENGL_ES_30)
    {
      const GLenum none = GL_NONE;
      glDrawBuffers(1, &none);
      glReadBuffer(none);
      }
#else
      {
        const GLenum none = GL_NONE;
        glDrawBuffer(none);
        glReadBuffer(none);
      }
#endif
      fLogC("Setting depth framebuffer failed");
      Framebuffer::bindScreenFramebuffer();
      break;
    case GL_COLOR_ATTACHMENT0:
      mTexture2D.bind();
      bindForRendering();
      mFramebuffer.attachTexture2D(GL_COLOR_ATTACHMENT0, target, mTexture2D.mTexture.getHandle());
      fLogC("Setting RGBA framebuffer failed");
      mTexture2D.unbind();
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
  glBlitFramebuffer(
    0
    , 0
    , mTexture2D.mCfg->mHeader.mWidth
    , mTexture2D.mCfg->mHeader.mHeight
    , 0
    , 0
    , mTexture2D.mCfg->mHeader.mWidth
    , mTexture2D.mCfg->mHeader.mHeight
    , GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void Texture2DRenderable::copyFrom(Framebuffer *source) {
  mFramebuffer.bindForWriting();
  source->bindForReading();
  source->setReadColorAttachment(0);
  glBlitFramebuffer(
    0
    , 0
    , mTexture2D.mCfg->mHeader.mWidth
    , mTexture2D.mCfg->mHeader.mHeight
    , 0
    , 0
    , mTexture2D.mCfg->mHeader.mWidth
    , mTexture2D.mCfg->mHeader.mHeight
    , GL_COLOR_BUFFER_BIT
    , GL_LINEAR); /* ... to finally copy it into main framebuffer */
}

void Texture2DRenderable::log() {
  // nothing
}

void Texture2DRenderable::reload() {
  mTexture2D.mTexture.reload();
  mTexture2D.reload();
  mFramebuffer.reload();
  setAttachment(mAttachment);
}

} /* flc */
} /* flw */
