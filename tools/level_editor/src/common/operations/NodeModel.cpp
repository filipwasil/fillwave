#include <algorithm>
#include "NodeModel.h"

namespace common {

namespace operations {

void NodeModel::addSceneModel(std::shared_ptr<objects::SceneModel> object) {
  mModel.push_back(object);
  //TODO: Emit change to controler and update view
}

NodeModel::NodeModel(QObject* parent)
  : QObject(parent) {
}

void NodeModel::addNodeToModel(objects::INodeBase* node, int modelId) {
  auto it = std::find_if(mModel.begin(), mModel.end(), [modelId = modelId](std::shared_ptr<objects::SceneModel>& ob) {
    return modelId == ob->getSceneID();
  });
  if (it == mModel.end()) {
    return;
  }
  // TODO: dodawanie obiektu do pozyskanego modelu
}
}
}