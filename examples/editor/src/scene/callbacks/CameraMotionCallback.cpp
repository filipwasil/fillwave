#include "CameraMotionCallback.h"
#include <fillwave/Fillwave.h>

namespace flw {
namespace flf {

CameraMotionCallback::CameraMotionCallback(Engine* engine)
	: Callback(EEventType::eTime), mTimePassed(0.0), mEngine(engine) {

}

void CameraMotionCallback::perform (EventType& event) {
	mTimePassed += TimeEvent::getData(event).mTimePassed;
	mEngine->getCurrentScene()->getCamera()->moveTo(calculateNewPosition(
	         mTimePassed));
}

glm::vec3 CameraMotionCallback::calculateNewPosition(float time) {
	return glm::vec3(15 * sin(time), 15.0, 15 * cos(time));
}

} /* framework */
} /* fillwave */
