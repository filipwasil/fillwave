#pragma once
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

namespace flw {
class Engine;
namespace flf {

class AnimationKeyboardCallback : public Callback {
public:
  AnimationKeyboardCallback(Entity *entity, eEventType eventType);

  virtual ~AnimationKeyboardCallback();

  void perform(EventType &event);

private:
  Entity *mEntity;
};
} /* flf */
} /* flw */
