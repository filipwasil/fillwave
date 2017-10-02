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

#include <fillwave/models/base/MoveableEased.h>

namespace flw {
namespace flf {

MoveableEased::MoveableEased(unsigned int aReservedSpaceForCallbacks)
		: mCallbackTimePassed(0)
		, mCurrentCallbackIdx(0)
    , mCallbackLoops(1) {
	mTimeCallbacks.reserve(aReservedSpaceForCallbacks);
}

void MoveableEased::waitInTime(float aDurationInSeconds) {
	mTimeCallbacks.push_back([this, aDurationInSeconds](float aDeltaTime) {
		mCallbackTimePassed += aDeltaTime;
		if (mCallbackTimePassed < aDurationInSeconds) {
			return 0.0f;
		}
		float timeLeft = mCallbackTimePassed - aDurationInSeconds;
		mCallbackTimePassed = 0;
		return timeLeft;
	});
}

void MoveableEased::moveByEased(float aDurationInSeconds,
                                const glm::vec3& deltaMove,
                                Callback<float(float)> aEase) {
	mTimeCallbacks.push_back([this, aDurationInSeconds, deltaMove, aEase](float aDeltaTime) {
		if (mCallbackTimePassed == 0.0f) {
			mBase.mTranslation = mTranslation;
		}
		mCallbackTimePassed += aDeltaTime;
		const float percentageDone = mCallbackTimePassed / aDurationInSeconds >= 1.0f ? 1.0f : mCallbackTimePassed / aDurationInSeconds;
		moveTo(mBase.mTranslation +
		       aEase(percentageDone) * deltaMove);
		if (mCallbackTimePassed < aDurationInSeconds) {
			return 0.0f;
		}
		float timeLeft = mCallbackTimePassed - aDurationInSeconds;
		mCallbackTimePassed = 0;
		return timeLeft;
	});
}

void MoveableEased::scaleByEased(float aDurationInSeconds,
                                 const glm::vec3& aDeltaScale,
                                 Callback<float(float)> aEase) {
	mTimeCallbacks.push_back([this, aDurationInSeconds, aDeltaScale, aEase](float aDeltaTime) {
		if (mCallbackTimePassed == 0.0f) {
			mBase.mScale = mScale;
		}
		mCallbackTimePassed += aDeltaTime;
		const float percentageDone = mCallbackTimePassed / aDurationInSeconds >= 1.0f ? 1.0f : mCallbackTimePassed / aDurationInSeconds;
		scaleTo(mBase.mScale + aEase(percentageDone) * aDeltaScale);
		if (mCallbackTimePassed < aDurationInSeconds) {
			return 0.0f;
		}
		float timeLeft = mCallbackTimePassed - aDurationInSeconds;
		mCallbackTimePassed = 0;
		return timeLeft;
	});
}

void MoveableEased::rotateByEased(float aDurationInSeconds, const float aDeltaAngle, const glm::vec3& aAxis,
		Callback<float(float)> aEase) {
	mTimeCallbacks.push_back([this, aDurationInSeconds, aDeltaAngle, aAxis, aEase](float aDeltaTime) {
		if (mCallbackTimePassed == 0.0f) {
			mBase.mRotation = mRotation;
		}
		mCallbackTimePassed += aDeltaTime;
		const float percentageDone = mCallbackTimePassed / aDurationInSeconds >= 1.0f ? 1.0f : mCallbackTimePassed / aDurationInSeconds;
		rotateTo(mBase.mRotation);
		rotateBy(aAxis, aEase(percentageDone) * aDeltaAngle);
		if (mCallbackTimePassed < aDurationInSeconds) {
			return 0.0f;
		}
		float timeLeft = mCallbackTimePassed - aDurationInSeconds;
		mCallbackTimePassed = 0;
		return timeLeft;
	});
}

float MoveableEased::stepInTime(float delta) {
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

void MoveableEased::stop() {
	mTimeCallbacks.clear();
	mCurrentCallbackIdx = 0;
}

void MoveableEased::loop(int loops) {
	mCallbackLoops = loops;
}

} /* flf */
} /* flw */
