/*
 * Framebuffer.h
 *
 *  Created on: 3 Apr 2013
 *      Author: Filip Wasil
 */

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include <fillwave/core/GLObject.h>
#include <fillwave/common/PtrShared.h>
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

	void bind(GLuint id = 0) const;

	void attachTexture2D(GLenum attachment, GLenum target, GLuint textureHandle);

	void attachTexture2DDraw(
	   GLenum attachment,
	   GLenum target,
	   GLuint textureHandle);

	void bindForWriting(GLuint id = 0) const;

	void bindForReading(GLuint id = 0) const;

	void setReadColorAttachment(GLuint attachmentColor);

	void setReadDepthAttachment();

	virtual void reload();

	static void bindScreenFramebuffer();

	static void bindScreenFramebufferForReading();

	static void bindScreenFramebufferForWriting();
};

} /* core */
typedef framework::PtrShared<core::Framebuffer> pFramebuffer;
typedef std::unique_ptr<core::Framebuffer> puFramebuffer;
} /* fillwave */

#endif /* FRAMEBUFFER_H_ */
