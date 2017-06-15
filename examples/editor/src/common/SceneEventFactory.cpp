#include "SceneEventFactory.h"

namespace common {

flw::flf::KeyboardEventData SceneEventFactory::getDefaultKeyboardEvent(int key) {
  flw::flf::KeyboardEventData data;
  data.action = 1;
  data.key = key;
  data.mode = 0;
  data.scanCode = 0;
  return data;
}

flw::flf::KeyboardEventData SceneEventFactory::getKeyboardEvent(int action, int key, int mode, int scanCode) {
  flw::flf::KeyboardEventData data;
  data.action = action;
  data.key = key;
  data.mode = mode;
  data.scanCode = scanCode;
  return data;
}

flw::flf::CursorPositionEvent SceneEventFactory::getCursorPositionEvent(int x, int y) {
  flw::flf::CursorPositionEventData d;
  d.xPosition = x;
  d.yPosition = y;
  flw::flf::CursorPositionEvent event(d);
  return event;
}

}