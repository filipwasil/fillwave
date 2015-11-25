/*
 * CameraMotionCallback.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: filip
 */

#include "../../../linux/inc/CallbacksGLFW/CameraMotionCallback.h"

#include <fillwave/actions/Event.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace actions {

CameraMotionCallback::CameraMotionCallback():EngineCallback(eEventType::eTime),
                                             mTimePassed(0.0) {

}

CameraMotionCallback::~CameraMotionCallback() {

}

void CameraMotionCallback::perform (Engine* engine, EventType* event) {
   mTimePassed += TimeEvent::getData(event).mTimePassed;
   engine->getCurrentScene()->getCamera()->moveTo(calculateNewPosition(mTimePassed));
}

glm::vec3 CameraMotionCallback::calculateNewPosition(float time) {
   return glm::vec3(15*sin(time), 15.0, 15*cos(time));
}

} /* actions */
} /* fillwave */
