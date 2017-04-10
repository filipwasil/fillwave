/*
 * TimedScaleCallback.cpp
 *
 *  Created on: 15 May 2014
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

#include <fillwave/actions/callbacks/TimedScaleCallback.h>

namespace flw {
namespace flf {

TimedScaleCallback::TimedScaleCallback(Moveable *moveable,
    glm::vec3 normalizedScaleVec,
    GLfloat lifetime,
    EasingFunction easing)
    : TimedCallback(lifetime, easing), mEndScale(normalizedScaleVec), mMoveable(moveable) {

}

TimedScaleCallback::TimedScaleCallback(Moveable *moveable,
    GLfloat normalizedScale,
    GLfloat lifetime,
    EasingFunction easing)
    : TimedCallback(lifetime, easing), mEndScale(normalizedScale, normalizedScale, normalizedScale)
    , mMoveable(moveable) {

}

void TimedScaleCallback::performTime(TimeEventData &data) {
  if (getPercentageDone() == 0.0f) {
    mStartScale = mMoveable->getScale();
  }
  mTimePassed += data.mTimePassed;
  mMoveable->scaleTo(mStartScale + ease(getPercentageDone()) * (mEndScale - mStartScale));
}

} /* flf */
} /* flw */
