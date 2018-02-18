#include <algorithm>
#include "NodeModel.h"

namespace common {

namespace operations {

void NodeModel::addSceneModel(std::unique_ptr<objects::SceneModel>&& object) {
  mModel.push_back(std::move(object));
  //TODO: Emit change to controler and update view
}

NodeModel::NodeModel(QObject* parent)
  : QObject(parent) {
}

void NodeModel::addNodeToModel(objects::ANodeBase* node, quintptr modelId) {
  auto it = std::find_if(mModel.begin(), mModel.end(), [modelId = modelId](std::unique_ptr<objects::SceneModel>& ob) {
    return modelId == ob->getSceneID();
  });
  if (it == mModel.end()) {
    return;
  }
  (*it)->addNode(node);
}

std::shared_ptr<flw::Engine> NodeModel::getSceneEngine(quintptr sceneId) {
  auto scene = std::find_if(mModel.begin(), mModel.end(), [sceneId = sceneId](const auto &obj) {
    return sceneId == obj->getSceneID();
  });
  if (scene == mModel.end()) {
    return nullptr;
  }
  return (*scene)->getSceneEngine();
}
}
}