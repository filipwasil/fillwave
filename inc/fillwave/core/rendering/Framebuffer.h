/*
 * Framebuffer.h
 *
 *  Created on: 3 Apr 2013
 *      Author: Filip Wasil
 */

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/GLObject.h>

#include <memory>

namespace fillwave {
namespace core {

/*! \class Framebuffer
 * \brief FramebufferObject - FO.
 */

class Framebuffer: public GLObject {
public:
	Framebuffer(GLsizei howMany = 1);

	virtual ~Framebuffer();

	void bind(GLuint id = 0);

	void attachTexture2D(GLenum attachment, GLenum target, GLuint textureHandle);

	void attachTexture2DDraw(
			GLenum attachment,
			GLenum target,
			GLuint textureHandle);

	void bindForWriting(GLuint id = 0);

	void bindForReading(GLuint id = 0);

	void setReadColorAttachment(GLuint attachmentColor);

	void setReadDepthAttachment();

	virtual void reload();

	static void bindScreenFramebuffer();

	static void bindScreenFramebufferForReading();

	static void bindScreenFramebufferForWriting();
};

} /* core */
typedef std::shared_ptr<core::Framebuffer> pFramebuffer;
typedef std::unique_ptr<core::Framebuffer> puFramebuffer;

} /* fillwave */

#endif /* FRAMEBUFFER_H_ */
