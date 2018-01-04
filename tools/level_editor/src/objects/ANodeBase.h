#pragma once

#include <QObject>
#include <QStandardItemModel>
#include <fillwave/Fillwave.h>
#include "fillwave/models/Model.h"

namespace scene {
class AScene;
}

namespace objects {

class ANodeBase : public QObject {
 public:
  ANodeBase(QObject* parent, flw::flf::Model* nodeDataModel, qintptr id)
    : QObject(parent)
    , mNodeDataModel(nodeDataModel)
    , mNodeId(id) {
  }

  ~ANodeBase() override = default;

  virtual QVector<QStandardItemModel*> getStandardModelForData() = 0;

  virtual void AddObjectToScene(std::shared_ptr<scene::AScene> mSceneView) = 0; // TODO: Prawdopodbnie nie potrzebana

  flw::flf::Model* getEngineModel() {
    return mNodeDataModel;
  };

  qintptr getId() {
    return mNodeId;
  }

 protected:
  flw::flf::Model* mNodeDataModel; // Should be free by engine
  qintptr mNodeId;
};

}

