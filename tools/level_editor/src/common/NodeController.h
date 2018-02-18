#pragma once

#include <QtCore/QObject>
#include "common/operations/NodeModel.h"
#include "ENodeType.hpp"

namespace common {
class NodeData;

class NodeController : public QObject {
 Q_OBJECT

 public:

  explicit NodeController(QObject* parent = nullptr);

  ~NodeController() override = default;

  void addSceneModel(std::unique_ptr<objects::SceneModel>&& object);

  void addCreatedModelToScene(objects::ANodeBase* node, std::shared_ptr<flw::Engine> engine);

 public slots:

  void inspectorUpdate(const QModelIndex& index);

  void addNodeToModel(NodeData node);

 private:
  quintptr mCurrentScenId;
  std::unique_ptr<operations::NodeModel> mModel;
};

}
