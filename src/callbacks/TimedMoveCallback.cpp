/*
 * TimedMoveCallback.cpp
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/callbacks/TimedMoveCallback.h>
#include <fillwave/actions/events/TimeTEvent.h>
#include <fillwave/Log.h>

namespace fillwave {
namespace framework {

TimedMoveCallback::TimedMoveCallback(
   Moveable* moveable,
   glm::vec3 endPosition,
   GLfloat lifeTime,
   EasingFunction easing) :
	TimedCallback(lifeTime, [&] (TimeEventData& data) {
	if (getPercentageDone() == 0.0f) {
		mStartPosition = mMoveable->getTranslation();
	}
	mTimePassed += data.mTimePassed;
	mMoveable->moveTo(mStartPosition + ease(getPercentageDone()) * mEndPosition);} , easing),
	mStartPosition(glm::vec3(0.0)),
	mEndPosition(endPosition),
	mMoveable(moveable) {

}

} /* framework */
} /* fillwave */
