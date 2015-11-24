/*
 * FollowCustomCursorCallback.cpp
 *
 *  Created on: Nov 8, 2014
 *      Author: filip
 */

#include "../../../linux/inc/CallbacksGLFW/FollowCustomCursorCallback.h"

namespace fillwave {
namespace actions {

FollowCustomCursorCallback::FollowCustomCursorCallback():EngineCallback(eEventType::eCursorPosition) {

}

FollowCustomCursorCallback::~FollowCustomCursorCallback() {

}

void FollowCustomCursorCallback::perform (Engine* engine, EventType* event) {
   CursorPositionEventData e = CursorPositionEvent::getData(event);
   engine->getCurrentScene()->moveCursor(glm::vec2((e.xPosition/engine->getScreenSize()[0])*2.0 - 1.0,
                                                  -(e.yPosition/engine->getScreenSize()[1])*2.0 + 1.0));
}

} /* particles */
} /* fillwave */
