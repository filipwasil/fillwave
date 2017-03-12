#include <QMessageBox>
#include <QLabel>
#include "scene/Renderer.h"
#include "LoadMenu.h"
#include "loader/XmlLoader.h"
#include "loader/MenuWidgetFabric.h"

namespace loader {

LoadMenu::LoadMenu()
    : mDefaultScenerioMenu(QString("assets/SceneriosMenu/HelloWorld.xml")) {
}

QVBoxLayout *LoadMenu::createDefaultMainMenu(common::ISceneController *sceneController) {
  QList < QWidget * > menuWidgets = getMenuWidgetList(sceneController);
  if (menuWidgets.isEmpty()) {
    QMessageBox msgBox;
    msgBox.setText("Fail to load HelloWorld xml file!");
    msgBox.exec();
    return nullptr;
  }
  QVBoxLayout *vbox = getMainMenuVBoxLayout(menuWidgets);
  return vbox;
}

QList<QWidget *> LoadMenu::getMenuWidgetList(common::ISceneController *sceneControlle) const {
  loader::MenuWidgetFabric *widgetFabric = new loader::MenuWidgetFabric(sceneControlle);
  std::unique_ptr <loader::XmlLoader> loadMenuEntries = std::make_unique<loader::XmlLoader>(widgetFabric);
  QList < QWidget * > menuWidgets;
  menuWidgets = loadMenuEntries->load(mDefaultScenerioMenu);
  delete widgetFabric;
  return menuWidgets;
}

QVBoxLayout *LoadMenu::getMainMenuVBoxLayout(const QList<QWidget *> &menuWidgets) {
  QVBoxLayout *vbox = new QVBoxLayout();
  for (auto mWidget : menuWidgets) {
    QLabel *label = new QLabel(mWidget->accessibleName());
    vbox->addWidget(label);
    vbox->addWidget(mWidget);
  }
  vbox->setAlignment(Qt::AlignTop);
  return vbox;
}

QVBoxLayout *LoadMenu::createMainMenu(QString pathToFile) {
  return nullptr;
}
}