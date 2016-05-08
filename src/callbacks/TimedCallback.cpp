/*
 * TimedCallback.cpp
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/callbacks/TimedCallback.h>
#include <iostream>

namespace fillwave {
namespace framework {

TimedCallback::TimedCallback(GLfloat timeToFinish, TimeFunction foo, EasingFunction easing) :
	Callback([ & ](EventType & event) {
	TimeEventData e = TimeEvent::getData(event);
	if (mTime) {
		mTime(e);
	}
	checkTime(e.mTimePassed);
}, eEventType::eTime, timeToFinish), mEasing(easing), mTime(foo) {
}

GLfloat TimedCallback::ease(GLfloat progress) {
	return mEasing(progress);
}

} /* framework */
} /* fillwave */
