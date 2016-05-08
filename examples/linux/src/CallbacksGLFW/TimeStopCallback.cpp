/*
 * TimeStopCallback.cpp
 *
 *  Created on: 15 sty 2015
 *      Author: filip
 */

#include "../../../linux/inc/CallbacksGLFW/TimeStopCallback.h"

#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>
#include <fillwave/Log.h>

FLOGINIT("TimeStopCallback", FERROR | FFATAL)

namespace fillwave {
namespace framework {

TimeStopCallback::TimeStopCallback(Engine* engine)
	: Callback([ & ] (EventType & event) {
	KeyboardEventData data = KeyboardEvent::getData(event);
	/* You can handle Your callback directly here ... */
	if (data.key == GLFW_KEY_T &&
	      data.action == GLFW_PRESS) {
		if (mTimeOn) {
			mTimeOn = false;
			mEngine->configureTime(0.0);
		} else {
			mTimeOn = true;
			mEngine->configureTime(1.0);
		}
	}
}, eEventType::eKey), mTimeOn(GL_TRUE), mEngine(engine) {

}

} /* framework */
} /* fillwave */
