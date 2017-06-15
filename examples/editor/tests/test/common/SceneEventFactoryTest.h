#pragma once

#include <gtest/gtest.h>
#include <memory>
#include "common/SceneEventFactory.h"

class SceneEventFactoryTestFixture : public testing::Test {
protected:
  virtual void SetUp() override {
  }

  virtual void TearDown() override {
  }

  common::SceneEventFactory sut;
};
