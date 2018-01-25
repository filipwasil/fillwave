/*
 * BuilderEmiter.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <fillwave/models/builders/BuilderEmiter.h>
#include <fillwave/models/EmiterPointCPU.h>
#include <fillwave/models/EmiterPointGPU.h>
#include <fillwave/Fillwave.h>

namespace flw {
namespace flf {

BuilderEmiter::BuilderEmiter(Engine *engine)
    : mEngine(engine)
    , mEmitingSourceRate(0.3f)
    , mHowMany(1)
    , mColor(glm::vec4(1.0))
    , mAcceleration(glm::vec3(0.0))
    , mStartVelocity(glm::vec3(0.0))
    , mRobustnessVelocity(glm::vec3(0.0))
    , mStartPosition(glm::vec3(0.0))
    , mRobustnessPosition(glm::vec3(0.0))
    , mStartSize(1.0f)
    , mLifetime(1.0f)
    , mTexture(engine->storeTexture("255_255_255.color"))
    , mBlendingSource(GL_SRC_ALPHA)
    , mBlendingDestination(GL_ONE_MINUS_SRC_ALPHA)
    , mDepthTesting(GL_FALSE)
    , mAlphaCutOff(0.0f) {
}

pu<IEmiterPoint> BuilderEmiter::buildEmiterGPU() {
  return std::make_unique<EmiterPointGPU>(mEngine,
                                          mEmitingSourceRate,
                                          mHowMany,
                                          mColor,
                                          mAcceleration,
                                          mStartVelocity,
                                          mRobustnessVelocity,
                                          mStartPosition,
                                          mRobustnessPosition,
                                          mStartSize,
                                          mLifetime,
                                          mTexture,
                                          mBlendingSource,
                                          mBlendingDestination,
                                          mDepthTesting,
                                          mAlphaCutOff);
}

pu<IEmiterPoint> BuilderEmiter::buildEmiterCPU() {
  return std::make_unique<EmiterPointCPU>(mEngine,
                                          mEmitingSourceRate,
                                          mHowMany,
                                          mColor,
                                          mAcceleration,
                                          mStartVelocity,
                                          mRobustnessVelocity,
                                          mStartPosition,
                                          mRobustnessPosition,
                                          mStartSize,
                                          mLifetime,
                                          mTexture,
                                          mBlendingSource,
                                          mBlendingDestination,
                                          mDepthTesting,
                                          mAlphaCutOff);
}

BuilderEmiter &BuilderEmiter::setEmitingSourceRate(GLfloat emitingSourceRate) {
  mEmitingSourceRate = emitingSourceRate;
  return *this;
}

BuilderEmiter &BuilderEmiter::setHowMany(GLuint howmany) {
  mHowMany = howmany;
  return *this;
}

BuilderEmiter &BuilderEmiter::setColor(glm::vec4 color) {
  mColor = color;
  return *this;
}

BuilderEmiter &BuilderEmiter::setAcceleration(glm::vec3 acceleration) {
  mAcceleration = acceleration;
  return *this;
}

BuilderEmiter &BuilderEmiter::setStartVelocity(glm::vec3 startVelocity) {
  mStartVelocity = startVelocity;
  return *this;
}

BuilderEmiter &BuilderEmiter::setRobustnessVelocity(glm::vec3 robustnessVelocity) {
  mRobustnessVelocity = robustnessVelocity;
  return *this;
}

BuilderEmiter &BuilderEmiter::setStartPosition(glm::vec3 startPosition) {
  mStartPosition = startPosition;
  return *this;
}

BuilderEmiter &BuilderEmiter::setRobustnessPosition(glm::vec3 robustnessPosition) {
  mRobustnessPosition = robustnessPosition;
  return *this;
}

BuilderEmiter &BuilderEmiter::setStartSize(GLfloat size) {
  mStartSize = size;
  return *this;
}

BuilderEmiter &BuilderEmiter::setLifetime(GLfloat lifetime) {
  mLifetime = lifetime;
  return *this;
}

BuilderEmiter &BuilderEmiter::setTexture(flc::Texture *texture) {
  mTexture = texture;
  return *this;
}

BuilderEmiter &BuilderEmiter::setBlendingSource(GLenum sourceColor) {
  mBlendingSource = sourceColor;
  return *this;
}

BuilderEmiter &BuilderEmiter::setBlendingDestination(GLenum destinationColor) {
  mBlendingDestination = destinationColor;
  return *this;
}

BuilderEmiter &BuilderEmiter::setAlphaCutOff(GLfloat cutOffLevel) {
  mAlphaCutOff = cutOffLevel;
  return *this;
}

BuilderEmiter &BuilderEmiter::setDepthTesting(GLboolean depthTesting) {
  mDepthTesting = depthTesting;
  return *this;
}

} /* flf */
} /* flw */
