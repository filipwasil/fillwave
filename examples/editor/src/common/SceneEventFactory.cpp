#include "SceneEventFactory.h"

namespace common {

flw::flf::EventData SceneEventFactory::getDefaultKeyboardData(int key) {
  flw::flf::EventData data;
  data.mKey.action = 1;
  data.mKey.key = key;
  data.mKey.mode = 0;
  data.mKey.scanCode = 0;
  return data;
}

flw::flf::EventData SceneEventFactory::getKeyboardData(int action, int key, int mode, int scanCode) {
  flw::flf::EventData data;
  data.mKey.action = action;
  data.mKey.key = key;
  data.mKey.mode = mode;
  data.mKey.scanCode = scanCode;
  return data;
}

flw::flf::EventData SceneEventFactory::getCursorPositionData(int x, int y) {
  flw::flf::EventData d;
  d.mCursorPosition.xPosition = x;
  d.mCursorPosition.yPosition = y;
  return d;
}

}