#pragma once

#include <QtCore/QObject>
#include "common/operations/NodeModel.h"

namespace common {

class NodeController : public QObject {
 Q_OBJECT

 public:

  NodeController(QObject* parent = nullptr);

  ~NodeController() = default;

  void addSceneModel(std::shared_ptr<objects::SceneModel> object, std::shared_ptr<scene::AScene> scene);

 public slots:

  void inspectorUpdate(const QModelIndex& index);

  void addNodeToModel();

 private:
  int mCurrentScenId;
  std::unique_ptr<operations::NodeModel> mModel;
};

}
