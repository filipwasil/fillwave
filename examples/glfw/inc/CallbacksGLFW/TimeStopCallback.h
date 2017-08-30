#pragma once

#include <fillwave/Framework.h>

namespace flw {
class Engine;
namespace flf {

class TimeStopCallback : public Callback {
public:
  TimeStopCallback(Engine *engine);

  virtual ~TimeStopCallback();

  void perform(EventType &event);

private:
  bool mTimeOn;
  Engine *mEngine;
};

} /* flf */
} /* flw */
