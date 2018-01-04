#pragma once

#include <memory>
#include <QStandardItem>
#include <QStandardItemModel>
#include <objects/ANodeBase.h>
#include <scene/AScene.h>

namespace scene {
class AScene;
}


namespace objects {

class SceneModel : public QObject {
 public:
  SceneModel(quintptr id, std::shared_ptr<scene::AScene> sceneV);

  ~SceneModel() = default;

  ANodeBase* getSingleObject(quintptr objectId);

  void modelUpdated();

  std::shared_ptr<flw::Engine> getSceneEngine();

  quintptr getSceneID() const;

  void addNode(ANodeBase* node);

 private:
  void addNewNodeToScen(ANodeBase* node);

 protected:
  quintptr mSceneID;
  std::vector<ANodeBase*> mModelObjects;
  std::shared_ptr<scene::AScene> mSceneView;
};

}

