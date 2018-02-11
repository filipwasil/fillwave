/*
 * Copyright (c) 2018, Fillwave developers
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

#include <fillwave/common/Finishable.h>

namespace flw {
namespace flf {

Finishable::Finishable(float timeToFinish)
    : mFinished(false)
    , mTimeToFinish(timeToFinish)
    , mTimePassed(0.0f)
    , mPercentageDone(0.0f) {
  // nothing
}

Finishable::~Finishable() = default;

Finishable::Finishable(const Finishable& arg) = default;

Finishable& Finishable::operator= (const Finishable& postProcessingPass) = default;

void Finishable::checkTime(float timePassed) {
  mTimePassed += timePassed;
  if (mTimePassed > mTimeToFinish && mTimeToFinish != FILLWAVE_ENDLESS) {
    mTimePassed -= mTimeToFinish;
    finish();
  }
}

float Finishable::getPercentageDone() const {
  return mTimePassed / mTimeToFinish >= 1.0f ? 1.0f : mTimePassed / mTimeToFinish;
}

void Finishable::finish() {
  mFinished = true;
}

void Finishable::reset() {
  mFinished = false;
}

bool Finishable::isFinished() const {
  return mFinished;
}

} /* flf */
} /* flw */
