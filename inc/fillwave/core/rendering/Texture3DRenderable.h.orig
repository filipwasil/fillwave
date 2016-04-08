/*
 * Texture3DRenderable.h
 *
 *  Created on: Dec 1, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE3DRENDERABLE_H_
#define TEXTURE3DRENDERABLE_H_

#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/core/texturing/Texture3D.h>

namespace fillwave {
namespace core {

/*! \class Texture3DRenderable
 * \brief One can render to this texture and use the rendered 6 images as a 2D texture.
 */

class Texture3DRenderable: public Texture3D {
public:
	Texture3DRenderable(
			Texture2DFile* filePosX,
			Texture2DFile* fileNegX,
			Texture2DFile* filePosY,
			Texture2DFile* fileNegY,
			Texture2DFile* filePosZ,
			Texture2DFile* fileNegZ,
			core::Texture2DRenderable* texture,
			ParameterList& parameters);
	virtual ~Texture3DRenderable() = default;
	void resize(GLint width, GLint height);
	void bindForWriting();
	void bindForRendering();
	void setAttachment(GLenum attachment);
	void setAttachmentFace(GLenum face, GLenum attachment);
	void log();

protected:
	core::Texture2DRenderable* mShadowTexture;
};

} /* core */
typedef std::shared_ptr<core::Texture3DRenderable> pTexture3DRenderable;
} /* fillwave */

#endif /* TEXTURE3DRENDERABLE_H_ */
