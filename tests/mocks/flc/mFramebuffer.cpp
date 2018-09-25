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

#include <flw/flc/rendering/Framebuffer.h>
#include <flw/Log.h>

FLOGINIT_DEFAULT()

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#define GL_DRAW_FRAMEBUFFER GL_DRAW_FRAMEBUFFER_NV
#define GL_READ_FRAMEBUFFER GL_READ_FRAMEBUFFER_NV
#define glReadBuffer glReadBufferNV
#else
#endif

namespace flw {
namespace flc {

Framebuffer::Framebuffer(GLuint howMany) : mHowMany(howMany) {
  reload();
}

Framebuffer::~Framebuffer() {

}

void Framebuffer::bind(GLuint id) const {

}

void Framebuffer::attachTexture2D(GLenum attachment, GLenum target, GLuint textureHandle) {

}

void Framebuffer::bindScreenFramebuffer() {

}

void Framebuffer::setReadColorAttachment(GLuint attachmentColor) {

}

void Framebuffer::setReadDepthAttachment() {

}

void Framebuffer::bindForWriting(GLuint id) const {

}

void Framebuffer::bindForReading(GLuint id) const {

}

void Framebuffer::attachTexture2DDraw(GLenum attachment, GLenum target, GLuint textureHandle) {

}

void Framebuffer::bindScreenFramebufferForReading() {

}

void Framebuffer::bindScreenFramebufferForWriting() {

}

void Framebuffer::reload() {

}

} /* flc */
} /* flw */
