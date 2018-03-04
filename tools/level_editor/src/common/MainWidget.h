#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QSplitter>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTreeView>
#include <QTabWidget>
#include <QStandardItemModel>
#include <memory>
#include "scene/callbacks/StandardMouseEventHandler.h"
#include "common/operations/MainWindowNodeOperations.h"
#include "common/operations/MainWindowFileOperations.h"
#include "common/NodeController.h"

class QPushButton;

class Renderer;

class Panel;


namespace common {

class MainWindowNodeOperations;

class MainWidget : public QMainWindow {
 Q_OBJECT

 public:
  MainWidget(int argc, char* argv[], QWidget* parent = 0);

  virtual ~MainWidget();

 private:
  void createBarMenu();

  void initMainGui(QWidget*& leftWidget, QWidget*& rightWidget) const;

  static const int mWindowWidth = 800;
  static const int mWindowHeight = 400;
  QSplitter* mWidgetSplitter;
  QWidget* mCentralWidget;
  QTabWidget* mScensTab;
  Renderer* mRenderer;
  int mArgc;
  char** mArgv;
  QMenu* mFileMenu;
  QMenu* mEditMenu;
  QMenu* mToolsMenu;
  QMenu* mHelpMenu;
  std::unique_ptr<common::MainWindowNodeOperations> mNodeOperations;
  std::unique_ptr<common::operations::MainWindowFileOperations> mFileSystemOperations;
  std::unique_ptr<common::NodeController> mNodeController;
};

}

