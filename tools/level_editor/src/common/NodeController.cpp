#include <QModelIndex>
#include <QTableView>
#include <QVariant>
#include "NodeController.h"

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

void NodeController::addSceneModel(std::shared_ptr<objects::SceneModel> object, std::shared_ptr<scene::AScene> scene) {
  object->setSceneView(scene);
  mModel->addSceneModel(object);
}

void NodeController::addNodeToModel() {
  // Przekazanie nowo stworzonego noda do modelu
}

}