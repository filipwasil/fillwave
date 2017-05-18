#include "TimeStopCallback.h"
#include <fillwave/Fillwave.h>

namespace flw {
namespace flf {

TimeStopCallback::TimeStopCallback(Engine* engine)
	: Callback(eEventType::eKey), mTimeOn(GL_TRUE), mEngine(engine) {

}

TimeStopCallback::~TimeStopCallback() {

}

void TimeStopCallback::perform(EventType& event) {
	KeyboardEventData data = KeyboardEvent::getData(event);
	/* You can handle Your callback directly here ... */
//	if (data.key == GLFW_KEY_T &&
//	      data.action == GLFW_PRESS) {
//		if (mTimeOn) {
//			mTimeOn = false;
//			mEngine->configureTime(0.0);
//		} else {
//			mTimeOn = true;
//			mEngine->configureTime(1.0);
//		}
//	}
}

} /* actions */
} /* fillwave */
