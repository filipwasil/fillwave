#pragma once

#include <memory>
#include <fillwave/Fillwave.h>
#include "fillwave/actions/events/KeyboardTEvent.h"
#include "fillwave/actions/events/CursorPositionTEvent.h"

namespace common {

class SceneEventFactory {
public:
  flw::flf::KeyboardEventData getDefaultKeyboardEvent(int key);

  flw::flf::KeyboardEventData getKeyboardEvent(int action, int key, int mode, int scanCode);

  flw::flf::CursorPositionEvent getCursorPositionEvent(int x, int y);
};
}