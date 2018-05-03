#pragma once

#include <gtest/gtest.h>
#include "objects/items/BaseItem.h"

class BaseItemFixture : public testing::Test {
 protected:
  virtual void SetUp() override {
    sut = new objects::BaseItem(nullptr, QString("Test"), 0);
  }

  virtual void TearDown() override {
    delete sut;
  }

  objects::BaseItem* sut;
};
