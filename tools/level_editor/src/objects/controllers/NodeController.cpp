#include <memory>
#include "common/operations/SelectItemType.h"
#include "NodeController.h"
#include "objects/factories/ItemFactory.h"


namespace objects {
NodeController::NodeController(TreeItemModel* objectsModel, QTreeView* nodeView, std::shared_ptr<Engine> engine)
  : QObject(nullptr)
  , mObjectsModel(objectsModel)
  , mNodeTreeview(nodeView)
  , mEngine(engine) {
  //empty
}

bool NodeController::addNode(common::EItemType type, QString name) {
  ItemFactory factory;
  auto newItem = factory.create(type, name, nullptr, mEngine);
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