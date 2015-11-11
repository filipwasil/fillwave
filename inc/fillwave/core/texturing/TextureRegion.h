/*
 * TextureRegion.h
 *
 *  Created on: 5 Jun 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTUREREGION_H_
#define TEXTUREREGION_H_

#include <fillwave/core/texturing/Texture2D.h>

namespace fillwave {

namespace core {
class TextureRegion;
}

typedef std::shared_ptr<core::TextureRegion> pTextureRegion;

namespace core {

/*! \class TextureRegion
 * \brief Texture2D part.
 */

class TextureRegion {
public:
	TextureRegion(pTexture texture, GLfloat u1 = 0, GLfloat v1 = 0, GLfloat u2 =
			1, GLfloat v2 = 1);

	virtual ~TextureRegion() = default;
	pTexture getTexture();
	GLfloat convertU(GLfloat u);
	GLfloat convertV(GLfloat v);

private:
	GLfloat mU1;
	GLfloat mV1;
	GLfloat mU2;
	GLfloat mV2;
	pTexture mTexture;
};

} /* core */
static pTextureRegion buildTextureRegion(
		pTexture texture,
		GLfloat u1 = 0.0,
		GLfloat v1 = 0.0,
		GLfloat u2 = 1.0,
		GLfloat v2 = 1.0) {
	return pTextureRegion(new core::TextureRegion(texture, u1, v1, u2, v2));
} /* core */
} /* fillwave */

#endif /* TEXTUREREGION_H_ */
