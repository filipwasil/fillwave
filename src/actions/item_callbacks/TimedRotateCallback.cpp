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
				mStartRotation(glm::quat()),
				mStartAngle(0.0),
				mEndAngle(angle),
				mAxis(axis),
				mEntity(entity) {

}

void TimedRotateCallback::performTime(TimeEventData& data) {
	if (getPercentageDone() == 0.0) {
		mStartRotation = mEntity->getRotation();
	}
	mTimePassed += data.mTimePassed;
	mEntity->rotateTo(mStartRotation);
	mEntity->rotateBy(mAxis,
			mStartAngle + ease(getPercentageDone()) * mEndAngle);
}

} /* actions */
} /* fillwave */
