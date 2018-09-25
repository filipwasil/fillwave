#pragma once

#include <flw/Framework.h>

namespace flw {
class Engine;
namespace flf {

class ColorPickingCallback {
 public:
  explicit ColorPickingCallback(Engine* engine);

  virtual ~ColorPickingCallback() = default;

  void perform(const Event& eventType);

 private:
  Entity* mCurrentlyPicked;
  Engine* mEngine;
};

} /* flf */
} /* flw */
