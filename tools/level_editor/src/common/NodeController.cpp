#include <QModelIndex>
#include <QTableView>
#include <common/operations/MainWindowNodeOperations.h>
#include "objects/NodeFactory.h"

namespace common {
NodeController::NodeController(QObject* parent)
  : mCurrentScenId(0)
  , QObject(parent) {
  mModel = std::make_unique<operations::NodeModel>(this);
  //connect(mModel, &operations::NodeModel::elementInserted, this, &NodeController::elementInsertedToModel);
}

void NodeController::inspectorUpdate(const QModelIndex& index) {
  int row = index.row();
  if (row == -1) {
    return;
  }
}

void NodeController::addSceneModel(std::unique_ptr<objects::SceneModel> && object) {
  mModel->addSceneModel(std::move(object));
}

void NodeController::addNodeToModel(NodeData node) {
  auto sceneEngine = mModel->getSceneEngine(mCurrentScenId);
  if (!sceneEngine)
  {
    return;
  }
  objects::NodeFactory nFactory(sceneEngine);
  objects::ANodeBase* readyNode = nFactory.createNode(node.mType, node.name, node.mId);
  mModel->addNodeToModel(readyNode, mCurrentScenId);
}

}