#include "SceneModel.h"

namespace objects {
SceneModel::SceneModel(quintptr id)
  : mSceneID(id) {
}

INodeBase* SceneModel::getSignleObject(quintptr objectId) {
  return nullptr;
}

quintptr SceneModel::getSceneID() const {
  return mSceneID;
}

void SceneModel::addNode(INodeBase* node) {
  node->setParent(this);
  mModelObjects.push_back(node);
}

void SceneModel::setSceneView(std::shared_ptr<scene::AScene> sceneEngine) {
// TODO: Powinno być tylko w konstruktorze.
}

void SceneModel::addNewNodeToScen(INodeBase* node) {
// TODO: Na podstawie node dodanie go do silnika
}
}