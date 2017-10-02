#pragma once

/*
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
#include <fillwave/Math.h>
//#include <Event.h>
#include <fillwave/common/Easing.h>
#include <fillwave/common/Allocator.h>
#include <functional>
#include <algorithm>

namespace flw {
namespace flf {

class MoveableEased : public Moveable {
 public:
	explicit MoveableEased(unsigned int aReservedSpaceForCallbacks = 1);
	void waitInTime(float deltaTime);
	void moveByEased(float deltaTime, const glm::vec3& deltaMove, Callback<float(float)> ease = LinearInterpolation);
	void scaleByEased(float deltaTime, const glm::vec3& aScale, Callback<float(float)> ease = LinearInterpolation);
	void rotateByEased(float deltaTime, const float aAngle, const glm::vec3& aAxis, Callback<float(float)> ease = LinearInterpolation);
	void loop(int loops);
	void stop();
	float stepInTime(float delta);

	template <typename ...ARGS>
	void addCustomCallback(float deltaTime, Callback<float(float, ARGS...)> aAction, ARGS&&... args) {
		mTimeCallbacks.push_back([this, deltaTime, aAction, args...](float aDeltaTime) {
			if (mCallbackTimePassed == 0.0f) {
				aAction(0.0f, std::forward<ARGS...>(args...));
			}
			mCallbackTimePassed += aDeltaTime;
			aAction(mCallbackTimePassed/deltaTime >= 1.0f ? 1.0f : mCallbackTimePassed/deltaTime, args...);
			if (mCallbackTimePassed < deltaTime) {
				return 0.0f;
			}
			float timeLeft = mCallbackTimePassed - deltaTime;
			mCallbackTimePassed = 0;
			return timeLeft;
		});
	}

 private:
	float mCallbackTimePassed;
	unsigned int mCurrentCallbackIdx;
	vec<Callback<float(float)>> mTimeCallbacks;
	unsigned int mCallbackLoops;

	struct {
		glm::vec3 mTranslation;
		glm::vec3 mScale;
		glm::quat mRotation;
	} mBase;
};

} /* flf */
} /* flw */
