#pragma once

#include <memory>
#include <QAction>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTabWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <objects/controllers/NodeController.h>

#include "common/operations/UiFilesWindowsCreator.h"
#include "common/operations/UiWindowsCreator.h"
#include "common/widgets/DockWidget.h"
#include "scene/callbacks/StandardMouseEventHandler.h"
#include "objects/TreeItemModel.h"
#include "objects/controllers/NodeController.h"

class Renderer;

namespace common {

class UiWindowsCreator;

class MainWidget : public QMainWindow {
 Q_OBJECT

 public:
  MainWidget(int argc, char* argv[], QWidget* parent = Q_NULLPTR);

 ~MainWidget();

 private:
  void createBarMenu();

  void initMainGui();

  void createDock(QString dockName, QWidget* widget, QString actionName, QMenu* subMenu, Qt::DockWidgetArea dockArea);

  static const int mWindowWidth = 800;
  static const int mWindowHeight = 400;

  QWidget* mCentralWidget;
  QTabWidget* mScenesTab;
  Renderer* mRenderer;
  int mArgc;
  char** mArgv;
  QMenu* mFileMenu;
  QMenu* mEditMenu;
  QMenu* mToolsMenu;
  QMenu* mWindowsMenu;
  QMenu* mHelpMenu;
  QTreeView* mNodeTreeView;
  QTreeView* mFilesTreeView;
  QScrollArea* mInspectorArea;
  QTreeView* mObjectPropertiesView;
  scene::callbacks::StandardMouseEventHandler* mNodeMouseHandler;
  objects::TreeItemModel* mItemModel;
  objects::NodeController* mNodeController;
};

}

