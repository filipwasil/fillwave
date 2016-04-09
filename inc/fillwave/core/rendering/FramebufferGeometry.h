/*
 * FramebufferGeometry.h
 *
 *  Created on: 22 May 2015
 *      Author: Filip Wasil
 */

#ifndef FRAMEBUFFERGEOMETRY_H_
#define FRAMEBUFFERGEOMETRY_H_

#include <fillwave/core/rendering/Framebuffer.h>
#include <fillwave/core/texturing/Parameter.h>
#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/management/TextureSystem.h>

namespace fillwave {
class Engine;
namespace core {

/*! \class FramebufferGeometry
 * \brief Framebuffer with multiple color and depth attachments.
 */

class FramebufferGeometry: public Framebuffer {
 public:
	FramebufferGeometry(
	   framework::TextureSystem* textures,
	   GLuint width,
	   GLuint height,
	   GLuint colorBuffers,
	   GLuint depthBuffers);

	virtual ~FramebufferGeometry() = default;

	void bindAttachments();
	void setAttachments();
	void setAttachmentStencilDepth();
	void setAttachmentSummaryForReading();
	void setAttachmentSummaryForWriting();

	void resize(GLuint width, GLuint height);
	void reload();

 private:

	std::vector<GLenum> mColorBuffers;

	core::Texture2D *mDeferredColors, *mStencilDepth, *mSummary;

	const GLint mColorBufferSize;
	const GLint mSummaryBufferSize;
	const GLint mDepthStencilBufferSize;

	const GLenum mSummaryBuffer;
	const GLenum mNone;
};

} /* core */
typedef std::shared_ptr<core::FramebufferGeometry> puFramebufferGeometry;
} /* fillwave */
#endif /* FRAMEBUFFERGEOMETRY_H_ */
