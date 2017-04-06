#pragma once

#include <gmock/gmock.h>
#include "scene/AScene.h"

class SceneMock : public scene::AScene {
public:
  MOCK_METHOD1(updateValue, void(const std::pair<QString, QString> &value));

  MOCK_METHOD0(init, void());

  MOCK_METHOD0(perform, void());
};