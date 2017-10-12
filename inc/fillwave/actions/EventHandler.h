#pragma once

#include "fillwave/common/Aliases.h"
#include "fillwave/actions/Event.h"

namespace flw {
namespace flf {

class EventHandler {
 public:
  EventHandler (flf::eEventType t, std::function<void(const Event&)> h)
    : type(t)
    , handler(h) {
    // nothing
  }

  void handle(const flf::Event& event) const {
    if (type == event.getType()) {
      handler(event);
    }
  }

 private:
  const flf::eEventType type;
  const std::function<void(const Event&)> handler;
};

} /* flf */
} /* flw */
