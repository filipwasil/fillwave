#pragma once

#include <gtest/gtest.h>
#include "loader/MenuWidgetFabric.h"
#include "SceneControllerMock.h"

class MenuWidgetsFabricTestFixture : public testing::Test {
protected:
  virtual void SetUp() override {
    mSceneController = new SceneControllerMock();
    sut = new loader::MenuWidgetFabric(mSceneController);
  }

  virtual void TearDown() override {
    delete sut;
    sut = 0;
    delete mSceneController;
    mSceneController = 0;
  }

  loader::MenuWidgetFabric *sut;
  SceneControllerMock *mSceneController;
};

