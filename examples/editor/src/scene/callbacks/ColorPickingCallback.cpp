#include "ColorPickingCallback.h"
#include <fillwave/Fillwave.h>

namespace flw {
namespace flf {

ColorPickingCallback::ColorPickingCallback(Engine* engine)
	: mEngine(engine) {

}

void ColorPickingCallback::perform(const Event &event) {
	MouseButtonEventData e = event.getData();
//	if (e.mAction == GLFW_RELEASE) {
		mEngine->pick(e.mWhereX, e.mWhereY);
//	}
}

} /* framework */
} /* fillwave */
