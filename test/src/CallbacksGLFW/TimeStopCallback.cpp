/*
 * TimeStopCallback.cpp
 *
 *  Created on: 15 sty 2015
 *      Author: filip
 */

#include <CallbacksGLFW/TimeStopCallback.h>
#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>

FLOGINIT("TimeStopCallback", FERROR | FFATAL)

namespace fillwave {
namespace actions {

TimeStopCallback::TimeStopCallback():EngineCallback(eEventType::key), mTimeOn(GL_TRUE) {

}

TimeStopCallback::~TimeStopCallback() {

}

void TimeStopCallback::perform(Engine* engine, EventType* event) {
   KeyboardEventData data = KeyboardEvent::getData(event);
   /* You can handle Your callback directly here ... */
   if (data.key == GLFW_KEY_T &&
         data.action == GLFW_PRESS) {
      if (mTimeOn) {
         mTimeOn = false;
         engine->configureTime(0.0);
      } else {
         mTimeOn = true;
         engine->configureTime(1.0);
      }
   }
}

} /* actions */
} /* fillwave */
