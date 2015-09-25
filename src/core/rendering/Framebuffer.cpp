/*
 * Framebuffer.cpp
 *
 *  Created on: 3 April 2013
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/core/rendering/Framebuffer.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Framebuffer", FERROR | FFATAL | FDEBUG)

namespace fillwave {
namespace core {

Framebuffer::Framebuffer(GLsizei howMany)
		: GLObject(howMany) {
	reload();
}

Framebuffer::~Framebuffer() {
	glDeleteFramebuffers(mHowMany, mHandles);
}

void Framebuffer::bind(GLuint id) {
	glBindFramebuffer(GL_FRAMEBUFFER, mHandles[id]);
	FLOG_CHECK("glBindFramebuffer GL_FRAMEBUFFER");
}

void Framebuffer::bindForWriting(GLuint id) {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mHandles[id]);
	FLOG_CHECK("glBindFramebuffer GL_DRAW_FRAMEBUFFER");
}

void Framebuffer::bindForReading(GLuint id) {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mHandles[id]);
	FLOG_CHECK("glBindFramebuffer GL_READ_FRAMEBUFFER");
}

void Framebuffer::attachTexture2D(
		GLenum attachment,
		GLenum target,
		GLuint textureHandle) {
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, target, textureHandle, 0);
	FLOG_CHECK("Attach texture to framebuffer failed");
}

void Framebuffer::attachTexture2DDraw(
		GLenum attachment,
		GLenum target,
		GLuint textureHandle) {
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachment, target,
			textureHandle, 0);
	FLOG_CHECK(
			"attachTexture2DDraw failed. attachment: 0x%x, target: 0x%x, handle: 0x%x",
			attachment, target, textureHandle);
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
	FLOG_CHECK("Reloading");
}

} /* core */
} /* fillwave */
