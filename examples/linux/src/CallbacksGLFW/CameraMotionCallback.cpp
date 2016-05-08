/*
 * CameraMotionCallback.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: filip
 */

#include "../../../linux/inc/CallbacksGLFW/CameraMotionCallback.h"
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace framework {

CameraMotionCallback::CameraMotionCallback(Engine* engine)
	: Callback([ & ] (EventType & event) {
	mTimePassed += TimeEvent::getData(event).mTimePassed;
	mEngine->getCurrentScene()->getCamera()->moveTo(calculateNewPosition(
	         mTimePassed));
}, eEventType::eTime), mTimePassed(0.0), mEngine(engine) {

}

glm::vec3 CameraMotionCallback::calculateNewPosition(float time) {
	return glm::vec3(15 * sin(time), 15.0, 15 * cos(time));
}

} /* framework */
} /* fillwave */
