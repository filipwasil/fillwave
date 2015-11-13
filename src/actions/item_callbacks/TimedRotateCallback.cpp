/*
 * TimedRotateCallback.cpp
 *
 *  Created on: 13 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/TimedRotateCallback.h>
#include <fillwave/actions/KeyboardEvent.h>
#include <fillwave/actions/TimeEvent.h>

#include <fillwave/Math.h>

#include <iostream>

namespace fillwave {
namespace actions {

TimedRotateCallback::TimedRotateCallback(
		pEntity entity,
		glm::vec3 axis,
		GLfloat angle,
		GLfloat lifeTime,
		eEasing easing)
		:
				TimedCallback(lifeTime, easing),
				mEntity(entity),
				mStartRotation(glm::quat()),
				mStartAngle(0.0f),
				mEndAngle(angle),
				mAxis(axis) {

}

void TimedRotateCallback::performTime(TimeEventData& data) {
	if (getPercentageDone() == 0.0f) {
		mStartRotation = mEntity->getRotation();
	}
	mTimePassed += data.mTimePassed;
	mEntity->rotateTo(mStartRotation);
	mEntity->rotateBy(mAxis,
			mStartAngle + ease(getPercentageDone()) * mEndAngle);
}

} /* actions */
} /* fillwave */
