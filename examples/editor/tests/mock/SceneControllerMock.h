#pragma once

#include <gmock/gmock.h>
#include "common/ISceneController.h"

class SceneControllerMock : public common::ISceneController {
public:
  MOCK_METHOD1(addTranslator, void(common::IMenuWidgetTranslator
      *translator));

  MOCK_METHOD1(updateScenField, void(const std::pair<QString, QVariant>
      menuElement));

  MOCK_METHOD0(deleteTranslators, void());

  MOCK_METHOD1(registerNewScene, void(std::shared_ptr<scene::AScene>
      scen));
};
