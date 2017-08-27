#pragma once

#include <QObject>
#include <QStandardItemModel>
#include <fillwave/Fillwave.h>
#include "fillwave/models/Model.h"

namespace scene {
class AScene;
}

namespace objects {

class INodeBase : public QObject {
 public:
  virtual ~INodeBase() = default;

  virtual QVector<QStandardItemModel*> getStandardModelForData() = 0;

  virtual void AddObjectToScene(std::shared_ptr<scene::AScene> mSceneView) = 0;
};

}

