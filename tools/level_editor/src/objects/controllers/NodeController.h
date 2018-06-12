#pragma once

#include <QString>
#include "common/InternalTypes.h"
#include "common/operations/ICreateObjectsView.h"
#include "objects/TreeItemModel.h"

namespace objects {

class NodeController : public QObject {
 Q_OBJECT
 public:
  explicit NodeController(TreeItemModel* objectsModel);

 public slots:

  bool addNode(common::EItemType type, QString name);

  void createNode();

 private:
  objects::TreeItemModel* mObjectsModel;
  common::ICreateObjectsView* mView;
};
}


