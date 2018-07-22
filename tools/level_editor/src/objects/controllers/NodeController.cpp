#include <memory>
#include "common/operations/SelectItemType.h"
#include "NodeController.h"
#include "objects/factories/ItemFactory.h"


namespace objects {
NodeController::NodeController(TreeItemModel* objectsModel, QTreeView* nodeView)
  : QObject(nullptr)
  , mObjectsModel(objectsModel)
  , mNodeTreeview(nodeView) {
  //empty
}

bool NodeController::addNode(common::EItemType type, QString name) {
  ItemFactory factory;
  auto newItem = factory.create(common::EItemType::object, name, nullptr, std::shared_ptr<Engine>());
  return mObjectsModel->insertToModel(newItem, mNodeTreeview->currentIndex());
}

void NodeController::createNode() {
  std::unique_ptr<common::SelectItemType> chooseItem = std::make_unique<common::SelectItemType>();
  if (!chooseItem->show()) {
    return;
  }
  addNode(chooseItem->getItemType(), chooseItem->getItemName());
}

}