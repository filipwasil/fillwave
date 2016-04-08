/*
 * Texture2DRenderable.h
 *
 *  Created on: Aug 13, 2014
 *      Author: filip
 */

#ifndef TEXTURE2DRENDERABLE_H_
#define TEXTURE2DRENDERABLE_H_

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/rendering/Framebuffer.h>

namespace fillwave {
namespace core {

/*! \class Texture2DRenderable
 * \brief One can render to this texture and use the rendered image as a 2D texture.
 */

class Texture2DRenderable: public Texture2D {
  public:
	Texture2DRenderable(
	    GLenum attachment,
	    Texture2DFile* file,
	    ParameterList& parameters);

	virtual ~Texture2DRenderable() = default;

	void resize(GLint width, GLint height);

	void bindForWriting();
	void bindForRendering();
	void bindForReading();

	void setAttachment(GLenum attachment, GLenum target = GL_TEXTURE_2D);
	void attachTexture2DDraw(GLenum attachment, GLenum target, GLuint texHandle);
	void attachTexture2D(GLenum attachment, GLenum target, GLuint textureHandle);

	void copyTo(Framebuffer* source);
	void copyFrom(Framebuffer* source);

	virtual void reload();
	void log();

  private:
	puFramebuffer mFramebuffer;
	GLenum mAttachment;
};

} /* core */
typedef std::shared_ptr<core::Texture2DRenderable> pTexture2DRenderable;
typedef std::unique_ptr<core::Texture2DRenderable> puTexture2DRenderable;
} /* fillwave */
#endif /* TEXTURE2DRENDERABLE_H_ */
