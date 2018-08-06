#pragma once

#include <QString>
#include <QTreeView>
#include "common/InternalTypes.h"
#include "common/operations/ICreateObjectsView.h"
#include "objects/TreeItemModel.h"

namespace objects {

class NodeController : public QObject {
 Q_OBJECT
 public:
  explicit NodeController(TreeItemModel* objectsModel, QTreeView* nodeView, std::shared_ptr<Engine> engine);

 public slots:

  bool addNode(common::EItemType type, QString name);

  void createNode();

 private:
  objects::TreeItemModel* mObjectsModel;
  QTreeView* mNodeTreeview;
  common::ICreateObjectsView* mView;
  std::shared_ptr<Engine> mEngine;
};
}


