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
  fLogC("attachTexture2DDraw failed. attachment: ", attachment, ", target: ", target, ", handle: ", textureHandle);
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
