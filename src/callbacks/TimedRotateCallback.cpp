/*
 * TimedRotateCallback.cpp
 *
 *  Created on: 13 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/callbacks/TimedRotateCallback.h>
#include <fillwave/actions/events/KeyboardTEvent.h>
#include <fillwave/actions/events/TimeTEvent.h>
#include <fillwave/Math.h>

#include <iostream>

namespace fillwave {
namespace framework {

TimedRotateCallback::TimedRotateCallback(
   Moveable* moveable,
   glm::vec3 axis,
   GLfloat angle,
   GLfloat lifeTime,
   EasingFunction easing) :
	TimedCallback(lifeTime, [&] (TimeEventData& data) {
					  if (getPercentageDone() == 0.0f) {
						  mStartRotation = mMoveable->getRotation();
					  }
					  mTimePassed += data.mTimePassed;
					  mMoveable->rotateTo(mStartRotation);
					  mMoveable->rotateBy(mAxis,
										  mStartAngle + ease(getPercentageDone()) * mEndAngle);
				  }
			, easing),
	mMoveable(moveable),
	mStartRotation(glm::quat()),
	mStartAngle(0.0f),
	mEndAngle(angle),
	mAxis(axis) {

}

} /* framework */
} /* fillwave */
