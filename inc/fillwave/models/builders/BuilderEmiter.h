#pragma once

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

#include <fillwave/models/base/IEmiterPoint.h>

namespace flw {
class Engine;
namespace flf {

/*! \class BuilderEmiter
 * \brief BuilderModel which builds the particles emiter.
 */

class BuilderEmiter {
public:
  BuilderEmiter(Engine* engine);

  BuilderEmiter &setEmitingSourceRate(GLfloat emitingSourceRate);

  BuilderEmiter &setHowMany(GLuint howmany);

  BuilderEmiter &setColor(glm::vec4 color);

  BuilderEmiter &setAcceleration(glm::vec3 acceleration);

  BuilderEmiter &setStartVelocity(glm::vec3 startVelocity);

  BuilderEmiter &setRobustnessVelocity(glm::vec3 robustnessVelocity);

  BuilderEmiter &setStartPosition(glm::vec3 startPosition);

  BuilderEmiter &setRobustnessPosition(glm::vec3 robustnessPosition);

  BuilderEmiter &setStartSize(GLfloat size);

  BuilderEmiter &setLifetime(GLfloat lifetime);

  BuilderEmiter &setTexture(flc::Texture2D* texture);

  BuilderEmiter &setBlendingSource(GLenum sourceColor);

  BuilderEmiter &setBlendingDestination(GLenum destinationColor);

  BuilderEmiter &setDepthTesting(GLboolean depthTesting);

  BuilderEmiter &setAlphaCutOff(GLfloat cutOffLevel);

  pu<IEmiterPoint> buildEmiterGPU();

  pu<IEmiterPoint> buildEmiterCPU();

private:
  Engine *mEngine;
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
  flc::Texture2D* mTexture;
  GLenum mBlendingSource;
  GLenum mBlendingDestination;
  GLboolean mDepthTesting;
  GLfloat mAlphaCutOff;
};

} /* flf */
} /* flw */
