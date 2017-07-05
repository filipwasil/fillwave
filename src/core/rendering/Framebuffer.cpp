/*
 * Framebuffer.cpp
 *
 *  Created on: 3 April 2013
 *      Author: Filip Wasil
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


#include <fillwave/core/rendering/Framebuffer.h>
#include <fillwave/Log.h>

FLOGINIT("Framebuffer", FERROR | FFATAL | FDEBUG)

namespace flw {
namespace flc {

Framebuffer::Framebuffer(GLuint howMany) : GLObject(howMany) {
  reload();
}

Framebuffer::~Framebuffer() {
  glDeleteFramebuffers(mHowMany, mHandles);
}

void Framebuffer::bind(GLuint id) const {
  glBindFramebuffer(GL_FRAMEBUFFER, mHandles[id]);
  fLogC("glBindFramebuffer GL_FRAMEBUFFER");
}

void Framebuffer::bindForWriting(GLuint id) const {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mHandles[id]);
  fLogC("glBindFramebuffer GL_DRAW_FRAMEBUFFER");
}

void Framebuffer::bindForReading(GLuint id) const {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, mHandles[id]);
  fLogC("glBindFramebuffer GL_READ_FRAMEBUFFER");
}

void Framebuffer::attachTexture2D(GLenum attachment, GLenum target, GLuint textureHandle) {
  glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, target, textureHandle, 0);
  fLogC("Attach texture to framebuffer failed");
}

void Framebuffer::attachTexture2DDraw(GLenum attachment, GLenum target, GLuint textureHandle) {
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachment, target, textureHandle, 0);
  fLogC("attachTexture2DDraw failed. attachment: 0x%x, target: 0x%x, handle: 0x%x", attachment, target, textureHandle);
}

void Framebuffer::setReadColorAttachment(GLuint attachmentColor) {
  glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentColor);
}

void Framebuffer::setReadDepthAttachment() {
  glReadBuffer(GL_DEPTH_ATTACHMENT);
}

void Framebuffer::bindScreenFramebuffer() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bindScreenFramebufferForReading() {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void Framebuffer::bindScreenFramebufferForWriting() {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Framebuffer::reload() {
  glGenFramebuffers(mHowMany, mHandles);
  fLogC("Reloading");
}

} /* flc */
} /* flw */
