#pragma once
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

namespace flw {
class Engine;
namespace flf {

class AnimationKeyboardCallback {
public:
  AnimationKeyboardCallback(Entity *entity);

  virtual ~AnimationKeyboardCallback();

  void perform(const Event& event);

private:
  Entity *mEntity;
};
} /* flf */
} /* flw */
