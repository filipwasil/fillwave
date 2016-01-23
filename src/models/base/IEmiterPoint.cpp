/*
 * IEmiterPoint.cpp
 *
 *  Created on: 16 Jun 2014
 *      Author: Filip Wasil
 */

#include <fillwave/Fillwave.h>
#include <fillwave/models/base/IEmiterPoint.h>

FLOGINIT("Emiter", FERROR | FFATAL)

namespace fillwave {
namespace framework {

IEmiterPoint::IEmiterPoint(
		Engine* engine,
		GLuint howMany,
		GLfloat size,
		GLfloat lifetime,
		pTexture texture,
		glm::vec4 color,
		GLenum blendingSource,
		GLenum blendingDestination,
		GLboolean depthTesting,
		GLfloat alphaCutOff)
		:
				IReloadable(engine),
				Entity(GL_POINTS),
				mStartSize(size),
				mLifetime(lifetime),
				mTexture(texture),
				mColor(color),
				mHowMany(howMany),
				mDepthTesting(depthTesting),
				mAlphaCutOff(alphaCutOff) {
	mRenderData.mBlend.mSrc = blendingSource;
	mRenderData.mBlend.mDst = blendingDestination;

#ifdef FILLWAVE_GLES_3_0
#else
	glEnable(GL_PROGRAM_POINT_SIZE);
	// glEnable(GL_POINT_SPRITE) always on since OpenGL 3.2 ... but not at all drivers ://////
	glEnable(GL_POINT_SPRITE);
#endif
}

void IEmiterPoint::setBlending(
		GLenum sourceFactor,
		GLenum destinationFactor) {
	mRenderData.mBlend.mSrc = sourceFactor;
	mRenderData.mBlend.mDst = destinationFactor;
}

void IEmiterPoint::updateRenderer(IRenderer& renderer) {
	GLuint id = mProgram.get()->getHandle();
	renderer.update(&id, this);
}

} /* framework */
} /* fillwave */
