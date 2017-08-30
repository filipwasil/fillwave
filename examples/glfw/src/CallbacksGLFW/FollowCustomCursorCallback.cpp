/*
 * FollowCustomCursorCallback.cpp
 *
 *  Created on: Nov 8, 2014
 *      Author: filip
 */

#include "CallbacksGLFW/FollowCustomCursorCallback.h"

namespace flw {
namespace flf {

FollowCustomCursorCallback::FollowCustomCursorCallback(Engine *engine)
    : Callback(eEventType::eCursorPosition)
    , mEngine(engine) {

}

void FollowCustomCursorCallback::perform(EventType &event) {
  CursorPositionEventData e = CursorPositionEvent::getData(event);
  mEngine->getCurrentScene()->getCursor()->move(
      glm::vec2((e.xPosition / mEngine->getScreenSize()[0]) * 2.0 - 1.0,
      -(e.yPosition / mEngine->getScreenSize()[1]) * 2.0 + 1.0));
}

} /* framework */
} /* fillwave */
