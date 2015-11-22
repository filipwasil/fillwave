/*
 * TimedMoveCallback.cpp
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/TimedMoveCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/extras/Log.h>

namespace fillwave {
namespace actions {

TimedMoveCallback::TimedMoveCallback(
		pMoveable moveable,
		glm::vec3 endPosition,
		GLfloat lifeTime,
		eEasing easing)
		: TimedCallback(lifeTime, easing), mStartPosition(glm::vec3(0.0)),
		mEndPosition(endPosition), mMoveable(moveable) {

}

void TimedMoveCallback::performTime(TimeEventData& data) {
	if (getPercentageDone() == 0.0f) {
		mStartPosition = mMoveable->getTranslation();
	}
	mTimePassed += data.mTimePassed;
	mMoveable->moveTo(mStartPosition + ease(getPercentageDone()) * mEndPosition);
}

} /* actions */
} /* fillwave */
