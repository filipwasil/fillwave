/*
 * IEmiterPoint.cpp
 *
 *  Created on: 16 Jun 2014
 *      Author: Filip Wasil
 */

#include <fillwave/Fillwave.h>
#include <fillwave/models/base/IEmiterPoint.h>
#include <fillwave/Log.h>

FLOGINIT("Emiter", FERROR | FFATAL)

namespace fillwave {
namespace framework {

IEmiterPoint::IEmiterPoint(
   Engine* engine,
   GLuint howMany,
   GLfloat size,
   GLfloat lifetime,
   core::Texture* texture,
   glm::vec4 color,
   GLenum blendingSource,
   GLenum blendingDestination,
   GLboolean depthTesting,
   GLfloat alphaCutOff) :
	IReloadable(engine),
	Entity(),
	mStartSize(size),
	mLifetime(lifetime),
	mTexture(texture),
	mColor(color),
	mHowMany(howMany),
	mDepthTesting(depthTesting),
	mAlphaCutOff(alphaCutOff) {
	mBlending.mSrc = blendingSource;
	mBlending.mDst = blendingDestination;

#ifdef FILLWAVE_GLES_3_0
#else
	glEnable(GL_PROGRAM_POINT_SIZE);
	// glEnable(GL_POINT_SPRITE) always on since OpenGL 3.2 ... but not at all drivers ://////
	glEnable(GL_POINT_SPRITE);
#endif
	if(glGetError() != GL_NO_ERROR) {
		FLOG_ERROR("Legacy features may cause a GL_INVALID_ENUM on core profile. It may happen.");
	}
}

void IEmiterPoint::setBlending(GLenum sourceFactor, GLenum destinationFactor) {
	mBlending.mSrc = sourceFactor;
	mBlending.mDst = destinationFactor;
}

void IEmiterPoint::updateRenderer(IRenderer& renderer) {
	renderer.update(this);
}

} /* framework */
} /* fillwave */
