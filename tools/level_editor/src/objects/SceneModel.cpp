#include <algorithm>
#include "SceneModel.h"
#include <fillwave/models/EmiterPointGPU.h>
#include <fillwave/loaders/ProgramLoader.h>

using namespace flw;
using namespace flw::flf;

namespace objects {
SceneModel::SceneModel(quintptr id, std::shared_ptr<scene::AScene> sceneV)
  : mSceneID(id)
  , mSceneView(sceneV) {
}

ANodeBase* SceneModel::getSingleObject(quintptr objectId) {
  auto output = std::find_if(mModelObjects.begin(), mModelObjects.end(), [objectId = objectId](const auto obj) {
    return objectId == obj->getId();
  });
  if (output == mModelObjects.end()) {
    return nullptr;
  }
  return *output;
}

quintptr SceneModel::getSceneID() const {
  return mSceneID;
}

void SceneModel::addNode(ANodeBase* node) {
  node->setParent(this);
  mModelObjects.push_back(node);
}

void SceneModel::addNewNodeToScen(ANodeBase* node) {
 //TODO: usunąć
}

void SceneModel::modelUpdated() {

}

std::shared_ptr<flw::Engine> SceneModel::getSceneEngine() {
  return mSceneView->getEngine();
}
}