/*
 * CameraFPPCallback.h
 *
 *  Created on: 11 mar 2015
 *      Author: filip
 */

#ifndef TEST_SRC_CALLBACKSGLFW_CAMERAFPPCALLBACK_H_
#define TEST_SRC_CALLBACKSGLFW_CAMERAFPPCALLBACK_H_

#include <fillwave/actions/EngineCallback.h>
#include <fillwave/Math.h>

namespace fillwave {
class Engine;
namespace actions {

class CameraFPPCallback: public actions::EngineCallback {
private:
   glm::vec4 mRelativePosition;
   glm::vec4 mRelativeLookAtPoint;
public:
   CameraFPPCallback(glm::vec3 relativePosition,
                     glm::vec3 relativeLookAtPoint);
   virtual ~CameraFPPCallback();
   void perform (Engine* engine, EventType* event);
};

} /* actions */
} /* fillwave */

#endif /* TEST_SRC_CALLBACKSGLFW_CAMERAFPPCALLBACK_H_ */
