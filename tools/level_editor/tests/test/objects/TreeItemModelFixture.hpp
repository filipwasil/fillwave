#pragma once

#include <gtest/gtest.h>
#include "objects/TreeItemModel.h"
#include "objects/items/BaseItem.h"

class TreeItemModelFixture : public testing::Test {
 protected:
  virtual void SetUp() override {
    mTestItem = new objects::BaseItem(nullptr, "TestObject");
    sut = new objects::TreeItemModel(QString("Test"));
  }

  virtual void TearDown() override {

    delete sut;
  }

  objects::TreeItemModel* sut;
  objects::BaseItem* mTestItem;
};
