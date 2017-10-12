#pragma once

#include <memory>
#include <fillwave/Fillwave.h>
#include "fillwave/actions/Event.h"

namespace common {

class SceneEventFactory {
public:
  flw::flf::KeyboardEventData getDefaultKeyboardEvent(int key);

  flw::flf::KeyboardEventData getKeyboardEvent(int action, int key, int mode, int scanCode);

  flw::flf::Event getCursorPositionEvent(int x, int y);
};
}