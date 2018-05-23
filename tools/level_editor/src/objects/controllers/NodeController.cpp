#include <memory>
#include "NodeController.h"
#include "objects/factories/ItemFactory.h"


namespace objects {
NodeController::NodeController(TreeItemModel* objectsModel, common::ICreateObjectsView* view)
  : mObjectsModel(objectsModel)
  , mView(view) {
}

bool NodeController::addNode(common::EItemType type, QString name) {
  ItemFactory factory;
  auto newItem = factory.create(common::EItemType::Object, name, nullptr);
  return mObjectsModel->insertToModel(newItem);;
}

}