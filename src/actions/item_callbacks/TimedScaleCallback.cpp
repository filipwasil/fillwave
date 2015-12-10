/*
 * TimedScaleCallback.cpp
 *
 *  Created on: 15 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/TimedScaleCallback.h>
#include <fillwave/actions/TimeEvent.h>

namespace fillwave {
namespace actions {

TimedScaleCallback::TimedScaleCallback(
		pMoveable moveable,
		glm::vec3 normalizedScaleVec,
		GLfloat lifetime,
		EasingFunction easing)
		:
				TimedCallback(lifetime, easing),
				mEndScale(normalizedScaleVec),
				mMoveable(moveable) {

}

TimedScaleCallback::TimedScaleCallback(
		pMoveable moveable,
		GLfloat normalizedScale,
		GLfloat lifetime,
		EasingFunction easing)
		:
				TimedCallback(lifetime, easing),
				mEndScale(normalizedScale, normalizedScale, normalizedScale),
				mMoveable(moveable) {

}

void TimedScaleCallback::performTime(TimeEventData& data) {
	if (getPercentageDone() == 0.0f) {
		mStartScale = mMoveable->getScale();
	}
	mTimePassed += data.mTimePassed;
	mMoveable->scaleTo(
			mStartScale + ease(getPercentageDone()) * (mEndScale - mStartScale));
}

} /* actions */
} /* fillwave */
