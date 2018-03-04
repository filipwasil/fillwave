#pragma once

#include <QTreeView>
#include <QStandardItemModel>
#include <QTableView>
#include "common/MainWidget.h"
#include "scene/callbacks/StandardMouseEventHandler.h"
#include "objects/ANodeBase.h"
#include "common/ENodeType.hpp"

namespace common {

struct NodeData
{
  NodeData(ENodeType type, quintptr id, const QString& name)
    : mType(type)
    , mId(id)
    , name(name) {
  }

  ENodeType mType = ENodeType::NONE;
  quintptr mId = 0;
  QString name;
};

class MainWindowNodeOperations : public QObject {
  Q_OBJECT
 public:
  MainWindowNodeOperations(QWidget* parent = nullptr);

  void newNodeDialog();

  virtual ~MainWindowNodeOperations();

  MainWindowNodeOperations(const MainWindowNodeOperations& mE) = default;

  MainWindowNodeOperations(MainWindowNodeOperations&& mE) = default;

  MainWindowNodeOperations& operator=(const MainWindowNodeOperations& mE) = default;

  MainWindowNodeOperations& operator=(MainWindowNodeOperations&& mE) = default;

  QVBoxLayout* createNodeWidget();

  QVBoxLayout* createInspectorView();

  QVBoxLayout* createOther();
signals:
  void addNewNode(NodeData node);
 private:
  QWidget *mParent;
  QTreeView* mScenTree;
  QStandardItemModel* mSceneModel;
  QTableView* mInspectorView;
  QTreeWidget* mOther;
  scene::callbacks::StandardMouseEventHandler* eventFilterMouse;
};

}

