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
    mView = new common::ICreateObjectsViewMock();
    sut = new objects::NodeController(mTreeModelMock, mView);
  }

  virtual void TearDown() override {
    delete sut;
  }

  objects::NodeController* sut;
  objects::TreeItemModelMock* mTreeModelMock;
  common::ICreateObjectsViewMock* mView;
};
