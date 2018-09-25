/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/flf/models/builders/BuilderEmiter.h>
#include <flw/flf/models/EmiterPointCPU.h>
#include <flw/flf/models/extended/EmiterPointGPU.h>
#include <flw/Fillwave.h>

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

BuilderEmiter &BuilderEmiter::setTexture(flc::Texture2D* texture) {
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
