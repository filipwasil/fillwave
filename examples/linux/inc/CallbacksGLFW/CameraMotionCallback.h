/*
 * CameraMotionCallback.h
 *
 *  Created on: Sep 24, 2014
 *      Author: filip
 */

#ifndef CAMERAMOTIONCALLBACK_H_
#define CAMERAMOTIONCALLBACK_H_

#include <fillwave/Framework.h>
#include <fillwave/Math.h>

namespace flw {
class Engine;
namespace flf {

/*! \class CameraMotionCallback
 * \brief EngineCallback to move the camera in circle road around point (0.0,0.0,0.0).
 */

class CameraMotionCallback : public Callback {
public:
  CameraMotionCallback(Engine *engine);

  virtual ~CameraMotionCallback() = default;

  void perform(EventType &event);

  glm::vec3 calculateNewPosition(float time);

private:
  float mTimePassed;
  Engine *mEngine;
};

} /* framework */
} /* fillwave */

#endif /* CAMERAMOTIONCALLBACK_H_ */
