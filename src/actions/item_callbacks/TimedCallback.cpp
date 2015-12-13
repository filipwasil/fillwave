/*
 * TimedCallback.cpp
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/Callback.h>
#include <fillwave/actions/TimedCallback.h>
#include <iostream>

namespace fillwave {
namespace actions {

TimedCallback::TimedCallback(GLfloat timeToFinish, EasingFunction easing)
		: Callback(eEventType::eTime, timeToFinish), mEasing(easing) {
}

void TimedCallback::perform(EventType& event) {
	TimeEventData e = TimeEvent::getData(event);
	performTime(e);
	checkTime(e.mTimePassed);
}

void TimedCallback::performTime(TimeEventData&) {
	// just wait
}

GLfloat TimedCallback::ease(GLfloat progress) {
	return mEasing(progress);
}

} /* actions */
} /* fillwave */
