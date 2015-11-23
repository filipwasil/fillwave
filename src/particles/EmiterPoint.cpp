/*
 * EmiterPoint.cpp
 *
 *  Created on: 16 Jun 2014
 *      Author: Filip Wasil
 */

#include <fillwave/particles/EmiterPoint.h>

FLOGINIT("Emiter", FERROR | FFATAL)

namespace fillwave {
namespace particles {

EmiterPoint::EmiterPoint(
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
				Reloadable(engine),
				mStartSize(size),
				mLifetime(lifetime),
				mTexture(texture),
				mColor(color),
				mHowMany(howMany),
				mDepthTesting(depthTesting),
				mAlphaCutOff(alphaCutOff) {
	mBlending.mSource = blendingSource;
	mBlending.mDestination = blendingDestination;

#ifdef FILLWAVE_GLES_3_0
#else
	glEnable(GL_PROGRAM_POINT_SIZE);
	// glEnable(GL_POINT_SPRITE) always on since OpenGL 3.2 ... but not at all drivers ://////
	glEnable(GL_POINT_SPRITE);
#endif
}

void EmiterPoint::setBlendingFunction(
		GLenum sourceFactor,
		GLenum destinationFactor) {
	mBlending.mSource = sourceFactor;
	mBlending.mDestination = destinationFactor;
}

} /* models */
} /* fillwave */
