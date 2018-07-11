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
    mTreeModelMock.reset(new objects::TreeItemModelMock());
    mTreeView.reset(new QTreeView());
    sut.reset(new objects::NodeController(mTreeModelMock.get(), mTreeView.get()));
  }
  std::unique_ptr<objects::NodeController> sut;
  std::unique_ptr<objects::TreeItemModelMock> mTreeModelMock;
  std::unique_ptr<QTreeView> mTreeView;
};
