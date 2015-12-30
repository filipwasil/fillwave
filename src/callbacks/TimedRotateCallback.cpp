/*
 * TimedRotateCallback.cpp
 *
 *  Created on: 13 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/callbacks/TimedRotateCallback.h>
#include <fillwave/actions/events/KeyboardEvent.h>
#include <fillwave/actions/events/TimeEvent.h>

#include <fillwave/Math.h>

#include <iostream>

namespace fillwave {
namespace framework {

TimedRotateCallback::TimedRotateCallback(
		pMoveable moveable,
		glm::vec3 axis,
		GLfloat angle,
		GLfloat lifeTime,
		EasingFunction easing)
		:
				TimedCallback(lifeTime, easing),
				mMoveable(moveable),
				mStartRotation(glm::quat()),
				mStartAngle(0.0f),
				mEndAngle(angle),
				mAxis(axis) {

}

void TimedRotateCallback::performTime(TimeEventData& data) {
	if (getPercentageDone() == 0.0f) {
		mStartRotation = mMoveable->getRotation();
	}
	mTimePassed += data.mTimePassed;
	mMoveable->rotateTo(mStartRotation);
	mMoveable->rotateBy(mAxis,
			mStartAngle + ease(getPercentageDone()) * mEndAngle);
}

} /* framework */
} /* fillwave */
