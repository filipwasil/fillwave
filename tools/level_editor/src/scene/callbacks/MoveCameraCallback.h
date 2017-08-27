#pragma once

#include <fillwave/actions/Event.h>

namespace flw {
class Engine;
namespace flf {

class MoveCameraCallback {
 private:
  float mSpeed;
  Engine* mEngine;
 public:
  MoveCameraCallback(Engine* engine, float speed = 1.0);

  virtual ~MoveCameraCallback() = default;

  virtual void perform(const flw::flf::Event& event);
};

} /* flf */
} /* flw */
