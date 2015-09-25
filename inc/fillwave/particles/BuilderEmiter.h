/*
 * BuilderEmiter.h
 *
 *  Created on: Apr 26, 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_PARTICLES_BUILDEREMITER_H_
#define INC_FILLWAVE_PARTICLES_BUILDEREMITER_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/particles/EmiterPoint.h>

namespace fillwave {

class Engine;

namespace particles {

/*! \class BuilderEmiter
 * \brief BuilderModel which builds the particles emiter.
 */

class BuilderEmiter {
public:
	BuilderEmiter(Engine* engine);

	virtual ~BuilderEmiter();

	BuilderEmiter& setEmitingSourceRate(GLfloat emitingSourceRate);

	BuilderEmiter& setHowMany(GLuint howmany);

	BuilderEmiter& setColor(glm::vec4 color);

	BuilderEmiter& setAcceleration(glm::vec3 acceleration);

	BuilderEmiter& setStartVelocity(glm::vec3 startVelocity);

	BuilderEmiter& setRobustnessVelocity(glm::vec3 robustnessVelocity);

	BuilderEmiter& setStartPosition(glm::vec3 startPosition);

	BuilderEmiter& setRobustnessPosition(glm::vec3 robustnessPosition);

	BuilderEmiter& setStartSize(GLfloat size);

	BuilderEmiter& setLifetime(GLfloat lifetime);

	BuilderEmiter& setTexture(pTexture texture);

	BuilderEmiter& setBlendingSource(GLenum sourceColor);

	BuilderEmiter& setBlendingDestination(GLenum destinationColor);

	BuilderEmiter& setDepthTesting(GLboolean depthTesting);

	BuilderEmiter& setAlphaCutOff(GLfloat cutOffLevel);

	pEmiterPoint buildEmiterGPU();

	pEmiterPoint buildEmiterCPU();

private:
	Engine* mEngine;
	GLfloat mEmitingSourceRate;
	GLuint mHowMany;
	glm::vec4 mColor;
	glm::vec3 mAcceleration;
	glm::vec3 mStartVelocity;
	glm::vec3 mRobustnessVelocity;
	glm::vec3 mStartPosition;
	glm::vec3 mRobustnessPosition;
	GLfloat mStartSize;
	GLfloat mLifetime;
	pTexture mTexture;
	GLenum mBlendingSource;
	GLenum mBlendingDestination;
	GLboolean mDepthTesting;
	GLboolean mAlphaCutOff;
};

} /* particles */
} /* fillwave */

#endif /* INC_FILLWAVE_PARTICLES_BUILDEREMITER_H_ */
