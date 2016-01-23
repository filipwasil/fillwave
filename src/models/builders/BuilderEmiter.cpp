/*
 * BuilderEmiter.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: filip
 */

#include <fillwave/models/builders/BuilderEmiter.h>
#include <fillwave/models/EmiterPointCPU.h>
#include <fillwave/models/EmiterPointGPU.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace framework {

BuilderEmiter::BuilderEmiter(Engine* engine)
		:
				mEngine(engine),
				mEmitingSourceRate(0.3),
				mHowMany(1),
				mColor(glm::vec4(1.0)),
				mAcceleration(glm::vec3(0.0)),
				mStartVelocity(glm::vec3(0.0)),
				mRobustnessVelocity(glm::vec3(0.0)),
				mStartPosition(glm::vec3(0.0)),
				mRobustnessPosition(glm::vec3(0.0)),
				mStartSize(1.0),
				mLifetime(1.0),
				mTexture(engine->storeTexture("255_255_255.color")),
				mBlendingSource(GL_SRC_ALPHA),
				mBlendingDestination(GL_ONE_MINUS_SRC_ALPHA),
				mDepthTesting(GL_FALSE),
				mAlphaCutOff(0.0) {
}

pIEmiterPoint BuilderEmiter::buildEmiterGPU() {
	return std::make_shared<EmiterPointGPU>(mEngine, mEmitingSourceRate, mHowMany,
					mColor, mAcceleration, mStartVelocity, mRobustnessVelocity,
					mStartPosition, mRobustnessPosition, mStartSize, mLifetime,
					mTexture, mBlendingSource, mBlendingDestination, mDepthTesting,
					mAlphaCutOff);
}

pIEmiterPoint BuilderEmiter::buildEmiterCPU() {
	return std::make_shared<EmiterPointCPU>(mEngine, mEmitingSourceRate, mHowMany, mColor,
					mAcceleration, mStartVelocity, mRobustnessVelocity,
					mStartPosition, mRobustnessPosition, mStartSize, mLifetime,
					mTexture, mBlendingSource, mBlendingDestination, mDepthTesting,
					mAlphaCutOff);
}

BuilderEmiter& BuilderEmiter::setEmitingSourceRate(GLfloat emitingSourceRate) {
	mEmitingSourceRate = emitingSourceRate;
	return *this;
}

BuilderEmiter& BuilderEmiter::setHowMany(GLuint howmany) {
	mHowMany = howmany;
	return *this;
}

BuilderEmiter& BuilderEmiter::setColor(glm::vec4 color) {
	mColor = color;
	return *this;
}

BuilderEmiter& BuilderEmiter::setAcceleration(glm::vec3 acceleration) {
	mAcceleration = acceleration;
	return *this;
}

BuilderEmiter& BuilderEmiter::setStartVelocity(glm::vec3 startVelocity) {
	mStartVelocity = startVelocity;
	return *this;
}

BuilderEmiter& BuilderEmiter::setRobustnessVelocity(
		glm::vec3 robustnessVelocity) {
	mRobustnessVelocity = robustnessVelocity;
	return *this;
}

BuilderEmiter& BuilderEmiter::setStartPosition(glm::vec3 startPosition) {
	mStartPosition = startPosition;
	return *this;
}

BuilderEmiter& BuilderEmiter::setRobustnessPosition(
		glm::vec3 robustnessPosition) {
	mRobustnessPosition = robustnessPosition;
	return *this;
}

BuilderEmiter& BuilderEmiter::setStartSize(GLfloat size) {
	mStartSize = size;
	return *this;
}

BuilderEmiter& BuilderEmiter::setLifetime(GLfloat lifetime) {
	mLifetime = lifetime;
	return *this;
}

BuilderEmiter& BuilderEmiter::setTexture(pTexture texture) {
	mTexture = texture;
	return *this;
}

BuilderEmiter& BuilderEmiter::setBlendingSource(GLenum sourceColor) {
	mBlendingSource = sourceColor;
	return *this;
}

BuilderEmiter& BuilderEmiter::setBlendingDestination(GLenum destinationColor) {
	mBlendingDestination = destinationColor;
	return *this;
}

BuilderEmiter& BuilderEmiter::setAlphaCutOff(GLfloat cutOffLevel) {
	mAlphaCutOff = cutOffLevel;
	return *this;
}

BuilderEmiter& BuilderEmiter::setDepthTesting(GLboolean depthTesting) {
	mDepthTesting = depthTesting;
	return *this;
}

} /* framework */
} /* fillwave */
