/*
 * CameraMotionCallback.h
 *
 *  Created on: Sep 24, 2014
 *      Author: filip
 */

#ifndef CAMERAMOTIONCALLBACK_H_
#define CAMERAMOTIONCALLBACK_H_

#include <fillwave/actions/EngineCallback.h>
#include <fillwave/Math.h>

namespace fillwave {
class Engine;
namespace actions {

/*! \class CameraMotionCallback
 * \brief EngineCallback to move the camera in circle road around point (0.0,0.0,0.0).
 */

class CameraMotionCallback: public EngineCallback {
private:
   float mTimePassed;
public:
   CameraMotionCallback();
   virtual ~CameraMotionCallback();
   void perform (Engine* engine, EventType* event);
   glm::vec3 calculateNewPosition(float time);
   };

} /* actions */
} /* fillwave */

#endif /* CAMERAMOTIONCALLBACK_H_ */
