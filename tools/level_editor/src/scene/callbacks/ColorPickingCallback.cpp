#include "ColorPickingCallback.h"
#include <flw/Fillwave.h>

namespace flw {
namespace flf {

ColorPickingCallback::ColorPickingCallback(Engine* engine)
  : mEngine(engine) {

}

void ColorPickingCallback::perform(const Event& event) {
  MouseButtonEventData e = event.getData();
//	if (e.mAction == GLFW_RELEASE) {
 // mEngine->pick(e.whereX, e.whereY);
//	}
}

} /* framework */
} /* fillwave */
