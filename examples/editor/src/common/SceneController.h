#pragma once

#include <QWidget>
#include <QVector>
#include <QMap>
#include <QVariant>
#include <memory>
#include "common/ISceneController.h"
#include "scene/AScene.h"
#include "common/translators/IMenuWidgetTranslator.h"

namespace common {
class SceneController : public common::ISceneController {
  Q_OBJECT
public :
  SceneController();

  SceneController(std::shared_ptr<scene::AScene> scen);

  void updateScenField(std::pair<QString, QVariant> menuElement);

  void addTranslator(translators::IMenuWidgetTranslator *translator);

  void deleteTranslators() override;

  void registerNewScene(std::shared_ptr<scene::AScene> scen) override;

  QMap<QString, QVariant> getCurrentMenuValues();
private:
  void reInitSceneValues();
  std::shared_ptr<scene::AScene> mScene;
  QVector<translators::IMenuWidgetTranslator *> mTranslators;
};
}

