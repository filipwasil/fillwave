/*
 * EmiterPointCPU.h
 *
 *  Created on: Sep 10, 2014
 *      Author: Filip Wasil
 */

#ifndef EMITER_POINT_CPU_H_
#define EMITER_POINT_CPU_H_

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
#include <fillwave/core/buffers/VertexBufferFloat.h>
#include <fillwave/core/operations/Query.h>

namespace fillwave {
namespace particles {

/*! \class EmiterPointCPU
 * \brief Polynomial particle Emiter.
 * Can generate a particles with velocity, direction,
 * and acceleration defined by the user.
 */

class EmiterPointCPU: public EmiterPoint {
public:
	EmiterPointCPU(
			Engine* engine,
			GLfloat emitingSourceRate,
			GLuint howMany,
			glm::vec4 color,
			glm::vec3 acceleration = glm::vec3(0.0),
			glm::vec3 startVelocity = glm::vec3(0.0),
			glm::vec3 robustnessVelocity = glm::vec3(0.0),
			glm::vec3 startPosition = glm::vec3(0.0),
			glm::vec3 robustnessPosition = glm::vec3(0.0),
			GLfloat startSize = 1.0,
			GLfloat lifetime = 6.0,
			pTexture texture = pTexture(),
			GLenum blendingSource = GL_SRC_ALPHA,
			GLenum blendingDestination = GL_ONE_MINUS_SRC_ALPHA,
			GLboolean depthTesting = GL_TRUE,
			GLfloat alphaCutOffLevel = 0.0);

	virtual ~EmiterPointCPU();

	void update(GLfloat timeElapsedSec);

	void draw(space::Camera& camera);

private:
	glm::vec3 mAcceleration;
	glm::vec3 mStartVelocity;
	glm::vec3 mStartPosition;
	glm::vec3 mCameraPosition;

	/* CD - Camera distance */

	pVertexBufferParticles mVBO;

	GLint mULCModelMatrix, mULCTextureUnit, mULCViewProjectionMatrix,
			mULCCameraPosition, mULCPointSize, mULCColor, mULCAcceleration,
			mULCLifeTime, mULCAlphaCutOff, mULCSourcePosition, mULCTimeElapsed;

	void initBuffers();

	void initPipeline();

	void initUniformsCache();

	void initVAO();

	void initVBO();

	void coreDraw();
};

} /* particles */
} /* fillwave */

#endif /* EMITER_POINT_CPU_H_ */
