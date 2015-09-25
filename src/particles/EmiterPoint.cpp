/*
 * EmiterPoint.cpp
 *
 *  Created on: 16 Jun 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
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
				Entity(),
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

#ifndef __ANDROID__
	glEnable(GL_PROGRAM_POINT_SIZE);
	//glEnable(GL_POINT_SPRITE); always on since OpenGL 3.2
#endif
}

EmiterPoint::~EmiterPoint() {

}

void EmiterPoint::setBlendingFunction(
		GLenum sourceFactor,
		GLenum destinationFactor) {
	mBlending.mSource = sourceFactor;
	mBlending.mDestination = destinationFactor;
}

} /* models */
} /* fillwave */
