#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include "loader/LoadMenu.h"
#include "common/SceneController.h"

class QPushButton;

class Renderer;

class Panel;

namespace common {
class MainWidget : public QMainWindow {
Q_OBJECT

public:
  MainWidget(int argc, char *argv[], QWidget *parent = 0);

  virtual ~MainWidget();

public slots:

  void loadNewScenario(QAction *action);

private:
  void createBarMenuActions();

  void createBarMenuCategories();

  QWidget *mCentralWidget;
  Renderer *mRenderer;
  int mArgc;
  char **mArgv;
  QMenuBar *mMenuBar;
  QMap<QString, QList<QAction *>> mActionsListMap;
  std::shared_ptr<SceneController> mSceneController;
  QVBoxLayout *mMenuLayout;
};

}

