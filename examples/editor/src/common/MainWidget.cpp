#include <memory>
#include "MainWidget.h"
#include "scene/Renderer.h"
#include "common/Tools.h"
#include "scene/ScensFactory.h"
#include "scene/sceneImp/TextScene.h"


namespace common {
MainWidget::MainWidget(int argc, char *argv[], QWidget *parent)
    : QMainWindow(parent), mCentralWidget(new QWidget(this)), mRenderer(new Renderer(argc, argv)), mArgc(argc), mArgv(
    argv) {
  createBarMenuActions();
  createBarMenuCategories();

  QVBoxLayout *horizontal = new QVBoxLayout();
  horizontal->setDirection(QBoxLayout::LeftToRight);
  QVBoxLayout *layoutEngineWindow = new QVBoxLayout();
  mSceneController = std::make_shared<SceneController>(mRenderer->getScen());
  loader::LoadMenu defaultMenu(mSceneController);
  mMenuLayout = defaultMenu.createDefaultMainMenu();
  horizontal->addLayout(mMenuLayout);

  mRenderer->setLayout(layoutEngineWindow);
  horizontal->addWidget(mRenderer);

  mCentralWidget->setLayout(horizontal);
  this->setCentralWidget(mCentralWidget);
  resize(800, 400);
}

MainWidget::~MainWidget() {

}

void MainWidget::createBarMenuActions() {
  auto scenesList = tools::readOnlyScenarioNames();
  QList<QAction *> scensActionList;
  for (auto sName : scenesList) {
    auto action = new QAction(sName, this);
    scensActionList.append(action);
  }
  mActionsListMap["Scens"] = scensActionList;
}

void MainWidget::createBarMenuCategories() {
  mMenuBar = this->menuBar();
  auto scens = mMenuBar->addMenu("Scens");
  if (!mActionsListMap.contains("Scens")) {
    return;
  }
  connect(scens, &QMenu::triggered, this, &MainWidget::loadNewScenario);
  auto ScensActionList = mActionsListMap["Scens"];
  for (auto action : ScensActionList) {
    scens->addAction(action);
  }
}

void MainWidget::loadNewScenario(QAction *action) {
  loader::LoadMenu newMenu(mSceneController);
  newMenu.recreateMenu(mMenuLayout, action->text());

  scene::ScensFactory scenFactory(mArgc, mArgv);
  auto scen = scenFactory.createScen(action->text());
  if (!scen) {
    return;
  }
  mSceneController->registerNewScene(scen);
  mRenderer->setNewScene(scen);
}
}
