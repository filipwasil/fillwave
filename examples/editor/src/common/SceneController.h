#pragma once

#include <QWidget>
#include <QVector>
#include <memory>
#include "common/ISceneController.h"
#include "scene/AScene.h"

namespace common {
class SceneController : public common::ISceneController {
  Q_OBJECT
public :
  SceneController();
  SceneController(std::shared_ptr<scene::AScene> scen);

  void updateScenField(QWidget *menuElement);

  void addTranslator(MenuWidgetTranslator *translator);

  void deleteTranslators() override;

  void registerNewScene(std::shared_ptr<scene::AScene> scen) override;
private:
  std::shared_ptr<scene::AScene> mScene;
  QVector<MenuWidgetTranslator *> mTranslators;
  QVariant getValue(const QWidget *menuElement) const;
};
}

