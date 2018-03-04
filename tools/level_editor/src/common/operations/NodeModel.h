#pragma once

#include <memory>
#include <vector>
#include <objects/SceneModel.h>
#include "scene/AScene.h"

namespace common {

namespace operations {

class NodeModel : public QObject {
 Q_OBJECT
 public:
  explicit NodeModel(QObject* parent);

  void addSceneModel(std::unique_ptr<objects::SceneModel> && object);

  std::shared_ptr<flw::Engine> getSceneEngine(quintptr sceneId);

  void addNodeToModel(objects::ANodeBase* node, quintptr modelId);

 signals:

  void elementInserted(std::shared_ptr<objects::SceneModel> element);
 private:
  std::vector<std::unique_ptr<objects::SceneModel>> mModel;
};

}
}