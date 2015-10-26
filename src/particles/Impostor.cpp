/*
 * Impostor.cpp
 *
 *  Created on: May 10, 2014
 *      Author: filip
 */

#include <fillwave/particles/Impostor.h>
#include <fillwave/Fillwave.h>

#include <fillwave/extras/Log.h>

FLOGINIT("Impostor", FERROR | FFATAL)

namespace fillwave {
namespace particles {

Impostor::Impostor(
		Engine* engine,
		GLfloat lifetime,
		GLfloat size,
		pTexture texture,
		GLenum blendingSource,
		GLenum blendingDestination)
		:
				Finishable(lifetime),
				mSize(size),
				mTexture(texture),
				mSampler(engine->storeSO(FILLWAVE_DIFFUSE_UNIT)) {
	mBlending.mSource = blendingSource;
	mBlending.mDestination = blendingDestination;
}

void Impostor::coreDraw() {
	if (mTexture) {
		mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
	}

	glEnable(GL_BLEND);
	glBlendFunc(mBlending.mSource, mBlending.mDestination);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisable(GL_BLEND);
	core::Texture2D::unbind2DTextures();
}

void Impostor::draw(space::Camera& camera) {

}

} /* models */
} /* fillwave */
