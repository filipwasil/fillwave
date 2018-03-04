#pragma once

#include <QTreeView>
#include <QStandardItemModel>
#include <QTableView>
#include <QScrollArea>
#include "common/MainWidget.h"
#include "scene/callbacks/StandardMouseEventHandler.h"

namespace common {

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

 private:
  QWidget* mParent;
  QTreeView* mScenTree;
  QStandardItemModel* mSceneModel;
  QTreeWidget* mOther;
  QScrollArea* mInspectorScrollArea;
  scene::callbacks::StandardMouseEventHandler* eventFilterMouse;
};

}

