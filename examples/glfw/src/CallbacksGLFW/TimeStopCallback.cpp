/*
 * TimeStopCallback.cpp
 *
 *  Created on: 15 sty 2015
 *      Author: filip
 */

#include <CallbacksGLFW/TimeStopCallback.h>

#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>

namespace flw {
namespace flf {

//TimeStopCallback::TimeStopCallback(Engine *engine)
//    : Callback(EEventType::eKey)
//    , mTimeOn(GL_TRUE)
//    , mEngine(engine) {
//
//}
//
//TimeStopCallback::~TimeStopCallback() {
//
//}
//
//void TimeStopCallback::perform(EventType &event) {
//  KeyboardEventData data = KeyboardEvent::getData(event);
//  /* You can handle Your callback directly here ... */
//  if (data.key == GLFW_KEY_T && data.action == GLFW_PRESS) {
//    if (mTimeOn) {
//      mTimeOn = false;
//      mEngine->configTime(0.0);
//    } else {
//      mTimeOn = true;
//      mEngine->configTime(1.0);
//    }
//  }
//}

} /* framework */
} /* fillwave */
