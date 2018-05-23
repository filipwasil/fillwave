#pragma once

#include "QString"
#include "objects/TreeItemModel.h"
#include "common/operations/ICreateObjectsView.h"
#include "common/InternalTypes.h"

namespace objects {

class NodeController {
 public:
  NodeController(TreeItemModel* objectsModel, common::ICreateObjectsView* view);

  bool addNode(common::EItemType type, QString name);

 private:
  objects::TreeItemModel* mObjectsModel;
  common::ICreateObjectsView* mView;
};
}


