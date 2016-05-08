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

TimedCallback::TimedCallback(GLfloat timeToFinish, EasingFunction easing) :
	Callback([ & ](EventType & event) {
	TimeEventData e = TimeEvent::getData(event);
	performTime(e);
	checkTime(e.mTimePassed);
}, eEventType::eTime, timeToFinish), mEasing(easing) {
}

void TimedCallback::performTime(TimeEventData&) {
	// just wait
}

GLfloat TimedCallback::ease(GLfloat progress) {
	return mEasing(progress);
}

} /* framework */
} /* fillwave */
