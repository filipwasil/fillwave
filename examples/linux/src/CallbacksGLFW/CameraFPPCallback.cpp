/*
 * CameraFPPCallback.cpp
 *
 *  Created on: 11 mar 2015
 *      Author: filip
 */

#include "../../../linux/inc/CallbacksGLFW/CameraFPPCallback.h"

#include <fillwave/actions/Event.h>
#include <fillwave/Fillwave.h>
#include <fillwave/actions/KeyboardEvent.h>
#include <fillwave/actions/MouseButtonEvent.h>

#include <GLFW/glfw3.h>

namespace fillwave {
namespace actions {


CameraFPPCallback::CameraFPPCallback(glm::vec3 relativePosition,
                                     glm::vec3 relativeLookAtPoint):EngineCallback(eEventType::eKey),
                                           mRelativePosition(relativePosition.x,
                                                             relativePosition.y,
                                                             relativePosition.z,
                                                             1.0),
                                           mRelativeLookAtPoint(relativeLookAtPoint.x,
                                                                relativeLookAtPoint.y,
                                                                relativeLookAtPoint.z,
                                                                1.0) {

}

CameraFPPCallback::~CameraFPPCallback() {

}

void CameraFPPCallback::perform (Engine* engine, EventType* event) {
   KeyboardEventData e = KeyboardEvent::getData(event);
   pCamera camera = engine->getCurrentScene()->getCamera();
   if (engine->getFocusKey() && e.action == GLFW_PRESS) {
      switch (e.key) {
         case GLFW_KEY_UP:
            engine->getFocusKey()->moveInDirection(glm::vec3(glm::vec4(0.0,0.0,0.1,1.0)));
            break;
         case GLFW_KEY_DOWN:
            engine->getFocusKey()->moveInDirection(glm::vec3(glm::vec4(0.0,0.0,-0.1,1.0)));
            break;
         case GLFW_KEY_LEFT:
            engine->getFocusKey()->rotateBy(glm::vec3(0.0,1.0,0.0), glm::radians(1.0f));
            break;
         case GLFW_KEY_RIGHT:
            engine->getFocusKey()->rotateBy(glm::vec3(0.0,1.0,0.0),  glm::radians(-1.0f));
            break;
      }
      engine->getFocusKey()->updateMatrixTree();
      glm::mat4 m = engine->getFocusKey()->getPhysicsMMC();
      camera->moveTo(glm::vec3(m*mRelativePosition));
//      camera->setEyeLookAt(glm::vec3(m*mRelativeLookAtPoint));
      camera->update();
   }
}

} /* actions */
} /* fillwave */
