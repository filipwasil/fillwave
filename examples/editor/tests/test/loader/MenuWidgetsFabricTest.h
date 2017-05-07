#pragma once

#include <gtest/gtest.h>
#include <memory>
#include "loader/MenuWidgetFabric.h"
#include "SceneControllerMock.h"

class MenuWidgetsFabricTestFixture : public testing::Test {
protected:
  virtual void SetUp() override {
    mSceneController = std::make_shared<SceneControllerMock>();
    sut = new loader::MenuWidgetFabric(mSceneController);
  }

  virtual void TearDown() override {
    delete sut;
    sut = 0;
  }

  loader::MenuWidgetFabric *sut;
  std::shared_ptr<SceneControllerMock> mSceneController;
};

