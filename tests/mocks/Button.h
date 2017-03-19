/*
 * Button.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: filip
 */

#pragma once

#include <fillwave/hud/Button.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace fillwave;
using namespace fillwave::framework;

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
