/*
 * TimedScaleCallback.cpp
 *
 *  Created on: 15 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/callbacks/TimedScaleCallback.h>
#include <fillwave/actions/events/TimeTEvent.h>

namespace fillwave {
namespace framework {

TimedScaleCallback::TimedScaleCallback(
   Moveable* moveable,
   glm::vec3 normalizedScaleVec,
   GLfloat lifetime,
   EasingFunction easing) :
	TimedCallback(lifetime, [&] (TimeEventData& data) {
		if (getPercentageDone() == 0.0f) {
			mStartScale = mMoveable->getScale();
		}
		mTimePassed += data.mTimePassed;
		mMoveable->scaleTo(
				mStartScale + ease(getPercentageDone()) * (mEndScale - mStartScale));
	}, easing),
	mEndScale(normalizedScaleVec),
	mMoveable(moveable) {

}

TimedScaleCallback::TimedScaleCallback(
   Moveable* moveable,
   GLfloat normalizedScale,
   GLfloat lifetime,
   EasingFunction easing) :
	TimedCallback(lifetime, [&] (TimeEventData& data) {
					  if (getPercentageDone() == 0.0f) {
						  mStartScale = mMoveable->getScale();
					  }
					  mTimePassed += data.mTimePassed;
					  mMoveable->scaleTo(
							  mStartScale + ease(getPercentageDone()) * (mEndScale - mStartScale));
				  }
			, easing),
	mEndScale(normalizedScale, normalizedScale, normalizedScale),
	mMoveable(moveable) {

}

} /* framework */
} /* fillwave */
