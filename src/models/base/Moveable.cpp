/*
 * Moveable.cpp
 *
 *  Created on: Jun 2, 2014
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


#include <fillwave/models/base/Moveable.h>

namespace flw {
namespace flf {

Moveable::Moveable(glm::vec3 translation, glm::quat rotation, unsigned int callbacksCount)
    : mTranslation(translation)
    , mRotation(rotation)
    , mScale(1.0f)
    , mRefresh(true)
    , mCallbackTimePassed(0)
    , mCurrentCallbackIdx(0)
    , mCallbackLoops(1) {
  mTimeCallbacks.reserve(callbacksCount);
}

Moveable::~Moveable() = default;

Moveable& Moveable::operator=(const Moveable&) = default;

Moveable::Moveable(const Moveable&) = default;

Moveable& Moveable::operator=(Moveable &&) = default;

Moveable::Moveable (Moveable&&) = default;

glm::vec3 Moveable::getTranslation() {
  return mTranslation;
}

void Moveable::moveTo(glm::vec3 coordinates) {
  mTranslation = coordinates;
  mRefresh = true;
}

void Moveable::moveToX(GLfloat distance) {
  mTranslation.x = distance;
  mRefresh = true;
}

void Moveable::moveToY(GLfloat distance) {
  mTranslation.y = distance;
  mRefresh = true;
}

void Moveable::moveToZ(GLfloat distance) {
  mTranslation.z = distance;
  mRefresh = true;
}

void Moveable::moveBy(glm::vec3 coordinates) {
  mTranslation += coordinates;
  mRefresh = true;
}

void Moveable::moveByX(GLfloat distance) {
  mTranslation.x += distance;
  mRefresh = true;
}

void Moveable::moveByY(GLfloat distance) {
  mTranslation.y += distance;
  mRefresh = true;
}

void Moveable::moveByZ(GLfloat distance) {
  mTranslation.z += distance;
  mRefresh = true;
}

void Moveable::moveInDirection(glm::vec3 direction) {
  mTranslation += glm::vec3(glm::mat4_cast(mRotation) * glm::vec4(direction, 1.0));
  mRefresh = true;
}

glm::vec3 Moveable::getScale() {
  return mScale;
}

void Moveable::scaleTo(GLfloat scale) {
  mScale = glm::vec3(scale, scale, scale);
  mRefresh = true;
}

void Moveable::scaleTo(glm::vec3 scale) {
  mScale = scale;
  mRefresh = true;
}

void Moveable::scaleToX(GLfloat scale) {
  mScale = glm::vec3(scale, mScale.y, mScale.z);
  mRefresh = true;
}

void Moveable::scaleToY(GLfloat scale) {
  mScale = glm::vec3(mScale.x, scale, mScale.z);
  mRefresh = true;
}

void Moveable::scaleToZ(GLfloat scale) {
  mScale = glm::vec3(mScale.x, mScale.y, scale);
  mRefresh = true;
}

glm::quat Moveable::getRotation() {
  return mRotation;
}

void Moveable::rotateTo(glm::quat rotation) {
  mRotation = rotation;
  mRefresh = true;
}

void Moveable::rotateTo(const glm::vec3 &axis, GLfloat angle) {
  glm::quat rotation = glm::angleAxis(angle, glm::normalize(axis));
  mRotation = rotation;
  mRefresh = true;
}

void Moveable::rotateByX(float angle) {
  rotateBy(glm::vec3(1.0, 0.0, 0.0), angle);
  mRefresh = true;
}

void Moveable::rotateByY(float angle) {
  rotateBy(glm::vec3(0.0, 1.0, 0.0), angle);
  mRefresh = true;
}

void Moveable::rotateByZ(float angle) {
  rotateBy(glm::vec3(0.0, 0.0, 1.0), angle);
  mRefresh = true;
}

void Moveable::rotateBy(const glm::vec3 &axis, GLfloat angle) {
  glm::vec3 Axis (glm::mat4_cast(mRotation) * glm::vec4(glm::normalize(axis), 1.0));

  Axis = Axis * sinf(angle / 2.0f);
  const float scalar = cosf(angle / 2.0f);
  const glm::quat offset(scalar, Axis.x, Axis.y, Axis.z);

  mRotation = offset * mRotation;
  mRotation = glm::normalize(mRotation);
  mRefresh = true;
}

void Moveable::updateMatrixCache() {
  mMMC = glm::translate(glm::mat4(1.0), mTranslation) * glm::mat4_cast(mRotation) * glm::scale(glm::mat4(1.0), mScale);
}

bool Moveable::isRefresh() const {
  return mRefresh;
}

void Moveable::setRefresh(bool state) {
  mRefresh = state;
}

glm::mat4 Moveable::getParentMMC() const {
  return mParentMMC;
}

glm::quat Moveable::getParentRotation() const {
  return mParentRotation;
}

void Moveable::attachTimeCallback(float deltaTime, Callback<float(float)> action) {
  mTimeCallbacks.push_back([this, deltaTime, action](float aDeltaTime) {
    if (0.0f == deltaTime) {
      return deltaTime;
    }
    if (mCallbackTimePassed == 0.0f) {
      action(0.0f);
    }
    mCallbackTimePassed += aDeltaTime;
    action(mCallbackTimePassed/deltaTime >= 1.0f ? 1.0f : mCallbackTimePassed/deltaTime);
    if (mCallbackTimePassed < deltaTime) {
      return 0.0f;
    }
    float timeLeft = mCallbackTimePassed - deltaTime;
    mCallbackTimePassed = 0;
    return timeLeft;
  });
}

void Moveable::waitInTime(float durationSec) {
  mTimeCallbacks.push_back([this, durationSec](float aDeltaTime) {
    mCallbackTimePassed += aDeltaTime;
    if (mCallbackTimePassed <= durationSec) {
      return 0.0f;
    }
    float timeLeft = mCallbackTimePassed - durationSec;
    mCallbackTimePassed = 0;
    return timeLeft;
  });
}

void Moveable::moveBy(float durationSec, const glm::vec3& deltaMove, Callback<float(float)> ease) {
  mTimeCallbacks.push_back([this, durationSec, deltaMove, ease](float aDeltaTime) {
    if (mCallbackTimePassed == 0.0f) {
      mBase.mTranslation = mTranslation;
    }
    mCallbackTimePassed += aDeltaTime;
    const float percentageDone = mCallbackTimePassed / durationSec >= 1.0f ? 1.0f : mCallbackTimePassed / durationSec;
    moveTo(mBase.mTranslation + ease(percentageDone) * deltaMove);
    if (mCallbackTimePassed <= durationSec) {
      return 0.0f;
    }
    float timeLeft = mCallbackTimePassed - durationSec;
    mCallbackTimePassed = 0;
    return timeLeft;
  });
}

void Moveable::moveTo(float durationSec, const glm::vec3& endTranslation, Callback<float(float)> ease) {
  mTimeCallbacks.push_back([this, durationSec, endTranslation, ease](float aDeltaTime) {
    if (mCallbackTimePassed == 0.0f) {
      mBase.mTranslation = mTranslation;
    }
    mCallbackTimePassed += aDeltaTime;
    const float percentageDone = mCallbackTimePassed / durationSec >= 1.0f ? 1.0f : mCallbackTimePassed / durationSec;
    const glm::vec3 deltaMove = endTranslation - mBase.mTranslation;
    moveTo(mBase.mTranslation + ease(percentageDone) * deltaMove);
    if (mCallbackTimePassed <= durationSec) {
      return 0.0f;
    }
    float timeLeft = mCallbackTimePassed - durationSec;
    mCallbackTimePassed = 0;
    return timeLeft;
  });
}


void Moveable::scaleBy(float durationSec, const glm::vec3& deltaScale, Callback<float(float)> ease) {
  mTimeCallbacks.push_back([this, durationSec, deltaScale, ease](float aDeltaTime) {
    if (mCallbackTimePassed == 0.0f) {
      mBase.mScale = mScale;
    }
    mCallbackTimePassed += aDeltaTime;
    const float percentageDone = mCallbackTimePassed / durationSec >= 1.0f ? 1.0f : mCallbackTimePassed / durationSec;
    const float easedProgress = ease(percentageDone);
    const glm::vec3 scale = mBase.mScale * ( deltaScale - glm::vec3(1.0) );
    scaleTo(mBase.mScale + easedProgress * scale);
    if (mCallbackTimePassed <= durationSec) {
      return 0.0f;
    }
    float timeLeft = mCallbackTimePassed - durationSec;
    mCallbackTimePassed = 0;
    return timeLeft;
  });
}

void Moveable::scaleTo(float durationSec, const glm::vec3& endScale, Callback<float(float)> ease) {
  mTimeCallbacks.push_back([this, durationSec, endScale, ease](float aDeltaTime) {
    if (mCallbackTimePassed == 0.0f) {
      mBase.mScale = mScale;
    }
    mCallbackTimePassed += aDeltaTime;
    const float percentageDone = mCallbackTimePassed / durationSec >= 1.0f ? 1.0f : mCallbackTimePassed / durationSec;
    const float easedProgress = ease(percentageDone);
    scaleTo(mBase.mScale + easedProgress * (endScale - mBase.mScale));
    if (mCallbackTimePassed <= durationSec) {
      return 0.0f;
    }
    float timeLeft = mCallbackTimePassed - durationSec;
    mCallbackTimePassed = 0;
    return timeLeft;
  });
}

void Moveable::rotateBy(float durationSec, const float endAngle, const glm::vec3& axis, Callback<float(float)> ease) {
  mTimeCallbacks.push_back([this, durationSec, endAngle, axis, ease](float aDeltaTime) {
    if (mCallbackTimePassed == 0.0f) {
      mBase.mRotation = mRotation;
    }
    mCallbackTimePassed += aDeltaTime;
    const float percentageDone = mCallbackTimePassed / durationSec >= 1.0f ? 1.0f : mCallbackTimePassed / durationSec;
    rotateTo(mBase.mRotation);
    rotateBy(axis, ease(percentageDone) * endAngle);
    if (mCallbackTimePassed < durationSec) {
      return 0.0f;
    }
    float timeLeft = mCallbackTimePassed - durationSec;
    mCallbackTimePassed = 0;
    return timeLeft;
  });
}

void Moveable::rotateTo(float durationSec, const float endAngle, const glm::vec3& axis, Callback<float(float)> ease) {
  mTimeCallbacks.push_back([this, durationSec, endAngle, axis, ease](float aDeltaTime) {
    if (mCallbackTimePassed == 0.0f) {
      mBase.mRotation = mRotation;
    }
    mCallbackTimePassed += aDeltaTime;
    const float percentageDone = mCallbackTimePassed / durationSec >= 1.0f ? 1.0f : mCallbackTimePassed / durationSec;
    rotateTo(axis, ease(percentageDone) * endAngle);
    rotateTo(glm::mix(mBase.mRotation, mRotation, ease(percentageDone)));
    if (mCallbackTimePassed < durationSec) {
      return 0.0f;
    }
    float timeLeft = mCallbackTimePassed - durationSec;
    mCallbackTimePassed = 0;
    return timeLeft;
  });
}

float Moveable::stepInTime(float delta) {
  if (mTimeCallbacks.empty() || mCurrentCallbackIdx == mTimeCallbacks.size()) {
    return delta;
  }
  float timeStillLeft = delta;
  do {
    timeStillLeft = mTimeCallbacks[mCurrentCallbackIdx](timeStillLeft);
    if (timeStillLeft == 0.0f) {
      return 0.0f;
    }
    mCallbackTimePassed = 0.0f;
    if (++mCurrentCallbackIdx < mTimeCallbacks.size()) {
      continue;
    }
    mCurrentCallbackIdx = 0;
    if (mCallbackLoops > 1) {
      mCallbackLoops--;
      continue;
    }
    mTimeCallbacks.clear();
    return timeStillLeft;
  } while(1);
}

void Moveable::stop() {
  mTimeCallbacks.clear();
  mCurrentCallbackIdx = 0;
}

void Moveable::loop(int loops) {
  mCallbackLoops = loops;
}

} /* flf */
} /* flw */
