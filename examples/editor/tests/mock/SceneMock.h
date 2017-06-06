#pragma once

#include <gmock/gmock.h>
#include "scene/AScene.h"

class SceneMock : public scene::AScene {
public:
  SceneMock(int argc, char * const* argv, QMap<QString, QVariant> parametersMap) : AScene(argc, argv, parametersMap) {}
  MOCK_METHOD0(init, void());

  MOCK_METHOD0(perform, void());
};