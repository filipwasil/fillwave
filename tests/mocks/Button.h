#pragma once

#include <fillwave/hud/Button.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace flw;
using namespace flw::flf;

class MockButton : public Button {
public:
  /* IPickable */
  MOCK_METHOD1(pick,
  void(glm::vec3
  color));
  MOCK_METHOD0(unpick,
  void());
  MOCK_METHOD0(onPicked,
  void());
  MOCK_METHOD0(onUnpicked,
  void());
};
