/*
 * Copyright (c) 2018, Fillwave developers
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
