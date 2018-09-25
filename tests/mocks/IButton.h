#pragma once

#include "../common.h"

#include <flw/flf/hud/Button.h>

using namespace flw;
using namespace flw::flf;

class MockButton : public Button {
public:
  MOCK_METHOD1(pick, void(glm::vec3 color));
  MOCK_METHOD0(unpick, void());
  MOCK_METHOD0(onPicked, void());
  MOCK_METHOD0(onUnpicked, void());
};
