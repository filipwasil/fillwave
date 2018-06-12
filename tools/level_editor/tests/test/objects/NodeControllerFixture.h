#pragma once

#include <gtest/gtest.h>
#include "objects/TreeItemModel.h"
#include "objects/items/BaseItem.h"
#include "objects/controllers/NodeController.h"
#include "objects/TreeItemModelMock.h"
#include "common/CreateObjectsViewMock.h"

class NodeControllerFixture : public testing::Test {
 protected:
  virtual void SetUp() override {
    mTreeModelMock = new objects::TreeItemModelMock();
    sut = new objects::NodeController(mTreeModelMock);
  }

  virtual void TearDown() override {
    delete sut;
    delete mTreeModelMock;
  }

  objects::NodeController* sut;
  objects::TreeItemModelMock* mTreeModelMock;
};
