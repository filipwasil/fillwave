#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QSplitter>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTabWidget>


class QPushButton;

class Renderer;

class Panel;

namespace common {
class MainWidget : public QMainWindow {
Q_OBJECT

public:
  MainWidget(int argc, char *argv[], QWidget *parent = 0);

  virtual ~MainWidget();

private:
  void createBarMenu();

  QVBoxLayout *createNodeWidget();

  QVBoxLayout *createFileSystemTree();

  QVBoxLayout *createInspectorView();

  QVBoxLayout *createOther();

  static const int mWindowWidth = 800;
  static const int mWindowHeight = 400;
  QSplitter *mWidgetSplitter;
  QWidget *mCentralWidget;
  QTabWidget *mScensTab;
  Renderer *mRenderer;
  int mArgc;
  char **mArgv;
  QMenu *mFileMenu;
  QMenu *mEditMenu;
  QMenu *mToolsMenu;
  QMenu *mHelpMenu;
  QTreeWidget *mScenTree;
  QTreeWidget *mFileSystemTree;
  QTreeWidget *mInspectorTree;
  QTreeWidget *mOther;
};

}

