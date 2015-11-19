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
#include <fillwave/actions/KeyboardEvent.h>
#include <fillwave/actions/MouseButtonEvent.h>
#include <fillwave/actions/ScrollEvent.h>

#include <GLFW/glfw3.h>

FLOGINIT("MoveCameraCallback", FERROR | FFATAL)

namespace fillwave {
namespace actions {

MoveCameraCallback::MoveCameraCallback(eEventType eventType,
                                       float speed,
                                       GLFWwindow* window):EngineCallback(eventType),
                                                    mSpeed(speed),
                                                    mWindow(window) {
   /*
    * If we want to rotate the camera using the mouse motion
    * cursor should not be visible
    *
    * */
   if (eventType == eEventType::cursorPosition && window) {
      glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
   }
}

MoveCameraCallback::~MoveCameraCallback() {

}

void MoveCameraCallback::perform (Engine* engine, EventType* event) {
   if (event->getType() == eEventType::key) {
      KeyboardEventData e = KeyboardEvent::getData(event);
      pCamera camera = engine->getCurrentScene()->getCamera();
      switch (e.key) {
         case GLFW_KEY_W:
            camera->moveInDirection(glm::vec3(0.0, 0.0, -mSpeed));
            break;
         case GLFW_KEY_S:
            camera->moveInDirection(glm::vec3(0.0, 0.0, mSpeed));
            break;
         case GLFW_KEY_D:
            if (e.action == GLFW_RELEASE) {
               engine->configureDebugger(eDebuggerState::toggleState);
            }
            break;
      }
   } else if (event->getType() == eEventType::mouseButton) {
      MouseButtonEventData e = MouseButtonEvent::getData(event);
      if (e.mButton == GLFW_MOUSE_BUTTON_LEFT) {
      }
      if (e.mButton == GLFW_MOUSE_BUTTON_MIDDLE) {
      }
      if (e.mButton == GLFW_MOUSE_BUTTON_RIGHT) {
      }
   } else if (event->getType() == eEventType::scroll) {
      ScrollEventData e = ScrollEvent::getData(event);
      if (e.mOffsetY < 0.0) { // scroll down
         engine->getCurrentScene()->getCamera()->moveBy(glm::vec3(0.0, 0.0, mSpeed));
      }
      else if (e.mOffsetY > 0.0) { // scroll up
         engine->getCurrentScene()->getCamera()->moveBy(glm::vec3(0.0, 0.0, -mSpeed));
      }
      return;
   } else if (event->getType() == eEventType::cursorPosition) {
      static bool init = false;
      static int  a = 0;
		auto d = [](double value){return static_cast<float>(value);};
      CursorPositionEventData e = CursorPositionEvent::getData(event);
      pCamera camera = engine->getCurrentScene()->getCamera();
      glm::ivec2 screenSize = engine->getScreenSize();
      double dx = e.xPosition - screenSize[0]/2;
      double dy = screenSize[1]/2 - e.yPosition;
      if (init) { /* debounce */
         camera->rotateBy(glm::vec3(0.0f,1.0f,0.0f), -mSpeed*d(glm::radians(dx)));
         camera->rotateBy(glm::vec3(1.0f,0.0f,0.0f), mSpeed*d(glm::radians(dy)));
         camera->update();
      } else {
         init = true;
      }
      if (mWindow) {
         if (a++>2){
            glfwSetCursorPos(mWindow, engine->getScreenSize()[0]/2,engine->getScreenSize()[1]/2);
            a=0;
         }
      }
   }

}

} /* actions */
} /* fillwave */
