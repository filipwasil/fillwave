#pragma once

#include <QIcon>
#include "objects/INodeBase.h"

namespace objects {
namespace standard {
class Sprite : public INodeBase {
 public:
  Sprite(qintptr nodeIde, flw::flf::Model* nodeDataModel);

  ~Sprite() = default;

  QVector<QStandardItemModel*> getStandardModelForData() override;

  void AddObjectToScene(std::shared_ptr<scene::AScene> mSceneView) override;

  std::string getObjectName();

 private:
  void init();

  qintptr mNodeIde;
  flw::flf::Model* mNodeDataModel;
  QVector<QStandardItemModel*> mTableModelRepersentation;
};
}
}
