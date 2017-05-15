#include <QMessageBox>
#include <QLabel>
#include <QLayoutItem>
#include "scene/Renderer.h"
#include "CreateMenu.h"
#include "loader/XmlLoader.h"
#include "loader/MenuWidgetFabric.h"
#include "common/Tools.h"

namespace loader {

CreateMenu::CreateMenu(std::shared_ptr<common::ISceneController> sceneController)
    : mSceneController(sceneController) {

}

QVBoxLayout *CreateMenu::createDefaultMainMenu() {
  QList<QWidget *> menuWidgets = getMenuWidgetList(QString("assets/SceneriosMenu/HelloWorld.xml"));
  if (menuWidgets.isEmpty()) {
    QMessageBox msgBox;
    msgBox.setText("Fail to load HelloWorld xml file!");
    msgBox.exec();
    return nullptr;
  }
  QVBoxLayout *vbox = getMainMenuVBoxLayout(menuWidgets);
  return vbox;
}

QList<QWidget *> CreateMenu::getMenuWidgetList(QString path) const {
  mSceneController->deleteTranslators();
  loader::MenuWidgetFabric *widgetFabric = new loader::MenuWidgetFabric(mSceneController);
  std::unique_ptr<loader::XmlLoader> loadMenuEntries = std::make_unique<loader::XmlLoader>(widgetFabric);
  QList<QWidget *> menuWidgets;
  menuWidgets = loadMenuEntries->load(path);
  delete widgetFabric;
  return menuWidgets;
}

QVBoxLayout *CreateMenu::getMainMenuVBoxLayout(const QList<QWidget *> &menuWidgets) {
  QVBoxLayout *vbox = new QVBoxLayout();
  fillLayoutWithWidgets(menuWidgets, vbox);
  return vbox;
}

void CreateMenu::fillLayoutWithWidgets(const QList<QWidget *> &menuWidgets, QVBoxLayout *vbox) const {
  for (auto mWidget : menuWidgets) {
    QLabel *label = new QLabel(mWidget->accessibleName());
    vbox->addWidget(label);
    vbox->addWidget(mWidget);
  }
  vbox->setAlignment(Qt::AlignTop);
}

void CreateMenu::recreateMenu(QVBoxLayout *VBLayout, QString sceneName) {
  auto newWidgetsList = getNewMainMenuWidgets(sceneName);
  clearLayout(VBLayout);
  fillLayoutWithWidgets(newWidgetsList, VBLayout);
}

QList<QWidget *> CreateMenu::getNewMainMenuWidgets(QString sceneName) {
  QString scenarioPath = getScenePath(sceneName);
  if (scenarioPath.isEmpty()) {
    QList<QWidget *> emptyList;
    return emptyList;
  }
  auto menuWidgetList = getMenuWidgetList(scenarioPath);
  return menuWidgetList;
}

QString CreateMenu::getScenePath(QString sceneName) {
  auto scenarioData = tools::readScenarioListWithPaths();
  auto itObj = std::find_if(scenarioData.begin(), scenarioData.end(), [&sceneName](auto o) {
    return o.first == sceneName;
  });
  if (itObj == scenarioData.end()) {
    return QString();
  }
  QString scenarioPath = (*itObj).second;
  return scenarioPath;
}

void CreateMenu::clearLayout(QVBoxLayout *VBLayout) {
  QLayoutItem *child;
  while ((child = VBLayout->takeAt(0)) != 0) {
    delete child;
  }
}


}