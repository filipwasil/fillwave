#pragma once
#include <gtest/gtest.h>
#include "common/operations/NodeModel.h"

class NodeModelFixture : public testing::Test {
  virtual void SetUp() override {
  }

  virtual void TearDown() override {
  }
 private:
  common::operations::NodeModel sut_;
};



