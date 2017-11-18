/*
 * ProgressBar.cpp
 *
 *  Created on: Jan 11, 2016
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

#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>
#include "Cluster.h"

namespace flw {
namespace flf {

Cluster::Cluster(Engine* engine,
    flc::Texture2D *texture,
    const std::string &shaderPath,
    glm::vec2 position,
    glm::vec2 scale)
    : IHUDNode(texture,
               ProgramLoader(engine).getHUDCustomFragmentShader(shaderPath),
               position,
               scale)
    , mSpeed(0.0f)
    , mRPM(0.0f)
    , mTimePassed(0.0f)
    , mEngine(engine) {

}

void Cluster::evaluateTime(float time) {
  mProgram->use();
  constexpr float speedFactor = 0.02f;
  mTimePassed += time * (mSpeed * speedFactor + 0.5f);
  if (mRPM < 315.0f) {
    mRPM+= 0.2f;
  } else if (mSpeed < 345.0f) {
    mSpeed += 0.2f;
  }
  mProgram->uniformPush("uTime", mTimePassed);
  mProgram->uniformPush("uSpeedAngle", mSpeed);
  mProgram->uniformPush("uRPMAngle", mRPM);
}

void Cluster::createGauge(
    int angleStep
    , int angleStart
    , int angleStop
    , int valueStart
    , int valueStop
    , glm::vec2 positionsCenter
    , float radius) {
  angleStep %= 360;
  angleStart %= 360;
  angleStop %= 360;
  if (angleStep <= 0 && angleStart - angleStop < angleStep) {
    // bad input data
    return;
  }

  const int angleSteps = (angleStop - angleStart)/angleStep;
  const int valueStep = (valueStop - valueStart)/angleSteps;

  int angle = angleStart;
  int value = valueStart;
  while (angle <= angleStop) {
    std::ostringstream oss;
    oss << value;
    std::string val = oss.str();
    float a = static_cast<float>(angle);
    const glm::vec2 screenSize = mEngine->getScreenSize();
    float f = screenSize.x/screenSize.y;
    float x = positionsCenter.x + ( radius * static_cast<float>(cos(glm::radians(-a - 90.f))) ) / f;
    float y = positionsCenter.y + ( radius * static_cast<float>(sin(glm::radians(-a - 90.f))) );
    mTexts.push_back(
        mEngine->storeText(val.c_str()
            , "fonts/bridgenorth"
            , glm::vec2(x, y)
            , 80.0
            , glm::vec4(1.0, 1.0, 1.0, 1.0)
            , ETextEffect::eBold));
    angle += angleStep;
    value += valueStep;
  }
}

void Cluster::setShift(unsigned int shift) {
  char shiftChar[] = {'0', '\0'};
  shiftChar[0] += shift;
  mShift = mEngine->storeText(
      shiftChar
      , "fonts/bridgenorth"
      , glm::vec2(-0.05, 0.25)
      , 400.0
      , glm::vec4(1.0, 1.0, 1.0, 1.0)
      , ETextEffect::eBold);
}

void Cluster::setSpeed(GLfloat speed) {
  mSpeed = speed;
}

void Cluster::setRPM(GLfloat rpm) {
  mRPM = rpm;
}

} /* flf */
} /* flw */
