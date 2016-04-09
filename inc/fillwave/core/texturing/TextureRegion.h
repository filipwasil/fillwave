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
	TextureRegion(
	   core::Texture2D* texture,
	   GLfloat u1 = 0,
	   GLfloat v1 = 0,
	   GLfloat u2 = 1,
	   GLfloat v2 = 1);

	virtual ~TextureRegion() = default;
	core::Texture2D* getTexture();
	GLfloat convertU(GLfloat u);
	GLfloat convertV(GLfloat v);

 private:
	GLfloat mU1;
	GLfloat mV1;
	GLfloat mU2;
	GLfloat mV2;
	core::Texture2D* mTexture;
};

} /* core */
pTextureRegion buildTextureRegion(
   core::Texture2D* texture = nullptr,
   GLfloat u1 = 0.0,
   GLfloat v1 = 0.0,
   GLfloat u2 = 1.0,
   GLfloat v2 = 1.0);
} /* fillwave */

#endif /* TEXTUREREGION_H_ */
