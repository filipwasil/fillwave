#pragma once

#include <gtest/gtest.h>
#include "common/SceneController.h"

class SceneControllerTestFixture : public testing::Test {
protected:
    virtual void SetUp() override {
        sut = 0;
    }

    virtual void TearDown() override {
        delete sut;
        sut = 0;
    }

    common::SceneController *sut;
};

