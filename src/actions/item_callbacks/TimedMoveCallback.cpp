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
		pEntity entity,
		glm::vec3 endPosition,
		GLfloat lifeTime,
		eEasing easing)
		: TimedCallback(lifeTime, easing), mStartPosition(glm::vec3(0.0)), /*to avoid warning*/
		mEndPosition(endPosition), mEntity(entity) {

}

void TimedMoveCallback::performTime(TimeEventData& data) {
	if (getPercentageDone() == 0.0f) {
		mStartPosition = mEntity->getTranslation();
	}
	mTimePassed += data.mTimePassed;
	mEntity->moveTo(mStartPosition + ease(getPercentageDone()) * mEndPosition);
}

} /* actions */
} /* fillwave */
