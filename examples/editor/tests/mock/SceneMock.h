#pragma once

#include <gmock/gmock.h>
#include "scene/AScene.h"

class SceneMock : public scene::AScene {
public:
  SceneMock(int argc, char ** argv) : AScene(argc, argv) {}
  MOCK_METHOD0(init, void());

  MOCK_METHOD0(perform, void());
};