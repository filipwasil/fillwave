#pragma once

#include <flw/Fillwave.h>
#include <flw/Framework.h>

namespace flw {
class Engine;
namespace flf {

class AnimationKeyboardCallback {
 public:
  explicit AnimationKeyboardCallback(Entity* entity);

  virtual ~AnimationKeyboardCallback();

  void perform(const Event& event);

 private:
  Entity* mEntity;
};
} /* flf */
} /* flw */
