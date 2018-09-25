#pragma once

#include <flw/Framework.h>
#include <flw/Fillwave.h>

namespace flw {
class Engine;
namespace flf {

class FollowCustomCursorCallback {
 public:
  explicit FollowCustomCursorCallback(Engine* engine);

  virtual ~FollowCustomCursorCallback() = default;

  void perform(const Event& event);

 private:
  Engine* mEngine;
};

} /* flf */
} /* flw */
