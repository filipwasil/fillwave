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
  NodeModel(QObject* parent);

  void addSceneModel(std::shared_ptr<objects::SceneModel> object);

  void addNodeToModel(objects::INodeBase* node, int modelId);

 signals:

  void elementInserted(std::shared_ptr<objects::SceneModel> element);
  //TODO: memory mangment checks.
 private:
  std::vector<std::shared_ptr<objects::SceneModel>> mModel;
};

}
}