#include "FollowCustomCursorCallback.h"

namespace flw {
namespace flf {

FollowCustomCursorCallback::FollowCustomCursorCallback(Engine* engine)
	:mEngine(engine) {

}

void FollowCustomCursorCallback::perform(const Event &event) {

	CursorPositionEventData e = event.getData().mCursorPosition;
  auto zero = e.yPosition;
  auto jeden = e.yPosition;
  //TODO: Bład segemtnacji
	mEngine->getCurrentScene()->getCursor()->move(glm::vec2((e.xPosition /
	                                       mEngine->getScreenSize()[0]) * 2.0 - 1.0,
	                                       -(e.yPosition / mEngine->getScreenSize()[1]) * 2.0 + 1.0));
}

} /* framework */
} /* fillwave */
