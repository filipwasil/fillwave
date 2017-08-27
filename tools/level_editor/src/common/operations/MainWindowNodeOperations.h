#pragma once

#include <QTreeView>
#include <QStandardItemModel>
#include <QTableView>
#include "common/MainWidget.h"
#include "scene/callbacks/StandardMouseEventHandler.h"

namespace common {


class MainWindowNodeOperations : public QObject {
 public:
  MainWindowNodeOperations(QObject* parent = nullptr);

  void newNodeDailog();

  virtual ~MainWindowNodeOperations();

  MainWindowNodeOperations(const MainWindowNodeOperations& mE) = default;

  MainWindowNodeOperations(MainWindowNodeOperations&& mE) = default;

  MainWindowNodeOperations& operator=(const MainWindowNodeOperations& mE) = default;

  MainWindowNodeOperations& operator=(MainWindowNodeOperations&& mE) = default;

  QVBoxLayout* createNodeWidget();

  QVBoxLayout* createInspectorView();

  QVBoxLayout* createOther();

 private:
  QTreeView* mScenTree;
  QStandardItemModel* mSceneModel;
  QTableView* mInspectorView;
  QTreeWidget* mOther;
  scene::callbacks::StandardMouseEventHandler* eventFilterMouse;
};

}

