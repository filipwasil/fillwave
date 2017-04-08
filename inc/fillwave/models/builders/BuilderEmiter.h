/*
 * BuilderEmiter.h
 *
 *  Created on: Apr 26, 2015
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
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

#ifndef INC_FILLWAVE_PARTICLES_BUILDEREMITER_H_
#define INC_FILLWAVE_PARTICLES_BUILDEREMITER_H_

#include <fillwave/models/base/IEmiterPoint.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class BuilderEmiter
 * \brief BuilderModel which builds the particles emiter.
 */

class BuilderEmiter {
public:
  BuilderEmiter(Engine *engine);

  virtual ~BuilderEmiter() = default;

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

  BuilderEmiter &setTexture(core::Texture *texture);

  BuilderEmiter &setBlendingSource(GLenum sourceColor);

  BuilderEmiter &setBlendingDestination(GLenum destinationColor);

  BuilderEmiter &setDepthTesting(GLboolean depthTesting);

  BuilderEmiter &setAlphaCutOff(GLfloat cutOffLevel);

  puIEmiterPoint buildEmiterGPU();

  puIEmiterPoint buildEmiterCPU();

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
  core::Texture *mTexture;
  GLenum mBlendingSource;
  GLenum mBlendingDestination;
  GLboolean mDepthTesting;
  GLfloat mAlphaCutOff;
};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_PARTICLES_BUILDEREMITER_H_ */
