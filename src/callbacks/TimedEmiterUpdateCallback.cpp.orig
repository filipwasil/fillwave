/*
 * TimedEmiterUpdateCallback.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: filip
 */

#include <fillwave/actions/callbacks/TimedEmiterUpdateCallback.h>
#include <fillwave/actions/events/TimeTEvent.h>
#include <fillwave/Log.h>

namespace fillwave {
namespace framework {

TimedEmiterUpdateCallback::TimedEmiterUpdateCallback(
		pIEmiterPoint emiter,
		GLfloat timeToFinish,
		EasingFunction easing) :
		TimedCallback(timeToFinish, easing), mEmiter(emiter), mTimePassed(0.0) {

}

void TimedEmiterUpdateCallback::performTime(TimeEventData& data) {
	mTimePassed += data.mTimePassed;
	mEmiter->update(mTimePassed);
}

} /* framework */
} /* fillwave */
