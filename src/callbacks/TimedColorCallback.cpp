/*
 * TimedColorCallback.cpp
 *
 *  Created on: 11 lut 2015
 *      Author: filip
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

#include <fillwave/actions/callbacks/TimedColorCallback.h>
#include <fillwave/actions/events/TimeEvent.h>
#include <fillwave/Log.h>

namespace fillwave {
namespace framework {

TimedColorCallback::TimedColorCallback(
   Model* model,
   glm::vec4 endColor,
   GLfloat lifeTime,
   EasingFunction easing) :
	TimedCallback(lifeTime, easing),
	mStartColor(glm::vec4(0.0)),
	mEndColor(endColor),
	mModel(model) {
	mPainter = std::make_shared<Painter>(mStartColor);
	mModel->addEffect(mPainter);
}

void TimedColorCallback::perform(EventType& event) {
	TimeEventData myData = TimeEvent::getData(event);
	if (getPercentageDone() == 0.0f) {
		mPainter->setColor(mStartColor);
	}
	mTimePassed += myData.mTimePassed;
	mPainter->setColor(mStartColor + ease(getPercentageDone()) * mEndColor);
	checkTime(myData.mTimePassed);
	if (mFinished) {
		mModel->removeEffect(mPainter);
	}
}

} /* framework */
} /* fillwave */

