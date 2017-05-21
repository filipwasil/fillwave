#pragma once

#include <memory>
#include <QWidget>
#include <QVBoxLayout>
#include <QMap>
#include "common/ISceneController.h"

namespace loader {

class CreateMenu {
public:
  CreateMenu(std::shared_ptr<common::ISceneController> sceneController);

  QVBoxLayout *createDefaultMainMenu();

  void recreateMenu(QVBoxLayout *VBLayout, QString sceneName);

protected:
  QString getScenePath(QString sceneName);

  void clearLayout(QLayout *VBLayout);

  QList<QWidget *> getMenuWidgetList(QString path) const;

  QList<QWidget *> getNewMainMenuWidgets(QString sceneName);

  QVBoxLayout *getMainMenuVBoxLayout(const QList<QWidget *> &menuWidgets);

  std::shared_ptr<common::ISceneController> mSceneController;

  void fillLayoutWithWidgets(const QList<QWidget *> &menuWidgets, QVBoxLayout *vbox) const;
};
}

