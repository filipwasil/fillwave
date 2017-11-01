#pragma once

#include <memory>
#include <fillwave/Fillwave.h>
#include "fillwave/actions/Event.h"

namespace common {

class SceneEventFactory {
public:
  flw::flf::EventData getDefaultKeyboardData(int key);

  flw::flf::EventData getKeyboardData(int action, int key, int mode, int scanCode);

  flw::flf::EventData getCursorPositionData(int x, int y);
};
}