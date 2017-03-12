#pragma once

#include <gmock/gmock.h>
#include "common/ISceneController.h"

class SceneControllerMock : public common::ISceneController {
public:
    MOCK_METHOD1(addTranslator, void(common::MenuWidgetTranslator *translator));

    MOCK_METHOD1(updateScenField, void(QWidget *menuElement));

    MOCK_METHOD0(deleteTranslators, void());
};
