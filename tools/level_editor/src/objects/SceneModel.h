#pragma once

#include <memory>
#include <QStandardItem>
#include <QStandardItemModel>
#include <objects/INodeBase.h>
#include <scene/AScene.h>

namespace scene {
class AScene;
}


namespace objects {

class SceneModel : public QObject {
 public:
  SceneModel(quintptr id);

  ~SceneModel() = default;

  INodeBase* getSignleObject(quintptr objectId);

  void modelUpdated() {
  };

  quintptr getSceneID() const;

  void addNode(INodeBase* node);

  void setSceneView(std::shared_ptr<scene::AScene> sceneEngine);

 private:
  void addNewNodeToScen(INodeBase* node);

 protected:
  quintptr mSceneID;
  std::vector<INodeBase*> mModelObjects;
  std::shared_ptr<scene::AScene> mSceneView;
};

}

