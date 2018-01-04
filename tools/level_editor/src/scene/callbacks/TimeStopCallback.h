#pragma once

#include <fillwave/Framework.h>

namespace flw {
class Engine;
namespace flf {

class TimeStopCallback {
 public:
  explicit TimeStopCallback(Engine* engine);

  virtual ~TimeStopCallback();

  void perform(const Event& event);

 private:
  bool mTimeOn;
  Engine* mEngine;
};

} /* flf */
} /* flw */
