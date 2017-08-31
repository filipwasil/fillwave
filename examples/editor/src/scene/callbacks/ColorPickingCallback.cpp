#include "ColorPickingCallback.h"
#include <fillwave/Fillwave.h>

namespace flw {
namespace flf {

ColorPickingCallback::ColorPickingCallback(Engine* engine)
	: Callback(EEventType::eMouseButton), mEngine(engine) {

}

void ColorPickingCallback::perform(EventType& event) {
	MouseButtonEventData e = MouseButtonEvent::getData(event);
//	if (e.mAction == GLFW_RELEASE) {
		mEngine->pick(e.mWhereX, e.mWhereY);
//	}
}

} /* framework */
} /* fillwave */
