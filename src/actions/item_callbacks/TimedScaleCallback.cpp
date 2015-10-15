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
		pEntity entity,
		glm::vec3 normalizedScaleVec,
		GLfloat lifetime,
		eEasing easing)
		:
				TimedCallback(lifetime, easing),
				mEndScale(normalizedScaleVec),
				mEntity(entity) {

}

TimedScaleCallback::TimedScaleCallback(
		pEntity entity,
		GLfloat normalizedScale,
		GLfloat lifetime,
		eEasing easing)
		:
				TimedCallback(lifetime, easing),
				mEndScale(normalizedScale, normalizedScale, normalizedScale),
				mEntity(entity) {

}

void TimedScaleCallback::performTime(TimeEventData& data) {
	if (getPercentageDone() == 0.0) {
		mStartScale = mEntity->getScale();
	}
	mTimePassed += data.mTimePassed;
	mEntity->scaleTo(
			mStartScale + ease(getPercentageDone()) * (mEndScale - mStartScale));
}

} /* actions */
} /* fillwave */
