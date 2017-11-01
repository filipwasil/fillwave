#pragma once
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

namespace flw {
class Engine;
namespace flf {

class AnimationKeyboardCallback {
public:
  AnimationKeyboardCallback(Model* model);

  virtual ~AnimationKeyboardCallback();

  void perform(const Event& event);

private:
  Model* mModel;
};
} /* flf */
} /* flw */
