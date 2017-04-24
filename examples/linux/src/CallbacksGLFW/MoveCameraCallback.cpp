/*
 * MoveCameraCallback.cpp
 *
 *  Created on: Jun 21, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include "../../../linux/inc/CallbacksGLFW/MoveCameraCallback.h"

#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>
#include <fillwave/Log.h>

FLOGINIT("MoveCameraCallback", FERROR | FFATAL)

namespace flw {
namespace flf {

MoveCameraCallback::MoveCameraCallback(Engine *engine, eEventType eventType, float speed, GLFWwindow *window)
    : Callback(eventType), mSpeed(speed), mWindow(window), mEngine(engine) {

  /*
   * If we want to rotate the camera using the mouse motion
   * cursor should not be visible
   *
   * */
  if (eventType == eEventType::eCursorPosition && window) {
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }
}

MoveCameraCallback::~MoveCameraCallback() {

}

void MoveCameraCallback::perform(EventType &event) {
  switch (event.getType())
  {
    case eEventType::eKey:
      {
        KeyboardEventData e = KeyboardEvent::getData(event);
        switch (e.key) {
          case GLFW_KEY_W:
            mEngine->getCurrentScene()->getCamera()->moveInDirection(glm::vec3(0.0, 0.0, -mSpeed));
            break;
          case GLFW_KEY_S:
            mEngine->getCurrentScene()->getCamera()->moveInDirection(glm::vec3(0.0, 0.0, mSpeed));
            break;
          case GLFW_KEY_D:
            if (e.action == GLFW_RELEASE) {
              mEngine->configureDebugger(eDebuggerState::eToggleState);
            }
            break;
        }
      }
      break;
    case eEventType::eMouseButton:
      {
        MouseButtonEventData e = MouseButtonEvent::getData(event);
        if (e.mButton == GLFW_MOUSE_BUTTON_LEFT) {
        }
        if (e.mButton == GLFW_MOUSE_BUTTON_MIDDLE) {
        }
        if (e.mButton == GLFW_MOUSE_BUTTON_RIGHT) {
        }
      }
      break;
    case eEventType::eScroll:
      {
        ScrollEventData e = ScrollEvent::getData(event);
        if (e.mOffsetY < 0.0) { // scroll down
          mEngine->getCurrentScene()->getCamera()->moveBy(glm::vec3(0.0, 0.0, mSpeed));
        } else if (e.mOffsetY > 0.0) { // scroll up
          mEngine->getCurrentScene()->getCamera()->moveBy(glm::vec3(0.0, 0.0, -mSpeed));
        }
      }
      break;
    case eEventType::eCursorPosition:
      {
        static bool init = false;
        static int a = 0;
        auto d = [](double value) {
          return static_cast<float>(value);
        };
        CursorPositionEventData e = CursorPositionEvent::getData(event);
        glm::ivec2 screenSize = mEngine->getScreenSize();
        double dx = e.xPosition - screenSize[0] / 2;
        double dy = screenSize[1] / 2 - e.yPosition;
        if (init) { /* debounce */
          mEngine->getCurrentScene()->getCamera()->rotateBy(glm::vec3(0.0f, 1.0f, 0.0f), -mSpeed * d(glm::radians(dx)));
          mEngine->getCurrentScene()->getCamera()->rotateBy(glm::vec3(1.0f, 0.0f, 0.0f), mSpeed * d(glm::radians(dy)));
          mEngine->getCurrentScene()->getCamera()->update();
        } else {
          init = true;
        }
        if (mWindow) {
          if (a++ > 2) {
            glfwSetCursorPos(mWindow, mEngine->getScreenSize()[0] / 2, mEngine->getScreenSize()[1] / 2);
            a = 0;
          }
        }
      }
      break;
    default:
      break;
  }
}

} /* framework */
} /* fillwave */
