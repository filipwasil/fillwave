#pragma once

#include <fillwave/Framework.h>

class GLFWwindow;
namespace flw {
class Engine;
namespace flf {

/*! \class MoveCameraCallback
 *
 * \brief Callback to move the current scene's camera.
 *
 */

class MoveCameraCallback : public Callback {
private:
  float mSpeed;
  GLFWwindow *mWindow;
  Engine *mEngine;
public:
  MoveCameraCallback(Engine *engine, eEventType eventType, float speed = 1.0, GLFWwindow *window = nullptr);

  virtual ~MoveCameraCallback();

  /* perform
   * \brief Performs EngineCallback action
   */

  virtual void perform(EventType &event);
};

} /* framework */
} /* fillwave */
