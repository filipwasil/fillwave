#include <memory>
#include "common/operations/SelectItemType.h"
#include "NodeController.h"
#include "objects/factories/ItemFactory.h"


namespace objects {
NodeController::NodeController(TreeItemModel* objectsModel)
  : QObject(nullptr)
  , mObjectsModel(objectsModel) {
  //empty
}

bool NodeController::addNode(common::EItemType type, QString name) {
  ItemFactory factory;
  auto newItem = factory.create(common::EItemType::object, name, nullptr);
  return mObjectsModel->insertToModel(newItem);
}

void NodeController::createNode() {
  std::unique_ptr<common::SelectItemType> chooseItem = std::make_unique<common::SelectItemType>();
  if (!chooseItem->show()) {
    return;
  }
  addNode(chooseItem->getItemType(), chooseItem->getItemName());
}

}