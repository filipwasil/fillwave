/*
 * TextureRegion.cpp
 *
 *  Created on: 5 Jun 2014
 *      Author: Filip Wasil
 */

#include <fillwave/core/texturing/TextureRegion.h>

namespace fillwave {
namespace core {

TextureRegion::TextureRegion(
		pTexture2D texture,
		GLfloat u1,
		GLfloat v1,
		GLfloat u2,
		GLfloat v2)
		: mU1(u1), mV1(v1), mU2(u2), mV2(v2), mTexture(texture) {

}

pTexture2D TextureRegion::getTexture() {
	return mTexture;
}

GLfloat TextureRegion::convertU(GLfloat u) {
	return mU1 + u * (mU2 - mU1);
}

GLfloat TextureRegion::convertV(GLfloat v) {
	return mV1 + v * (mV2 - mV1);
}

} /* core */
pTextureRegion buildTextureRegion(
		pTexture2D texture,
		GLfloat u1,
		GLfloat v1,
		GLfloat u2,
		GLfloat v2) {
	return std::make_shared<core::TextureRegion>(texture, u1, v1, u2, v2);
}
} /* fillwave */
