
#ifndef SceneControllerTest_H
#define SceneControllerTest_H

#include <gtest/gtest.h>
#include "loader/SceneController.h"

class SceneControllerTestFixture : public testing::Test {
protected:
    virtual void SetUp() override {
        sut = 0;
    }

    virtual void TearDown() override {
        delete sut;
        sut = 0;
    }

    loader::SceneController *sut;
};

#endif //SceneControllerTest_H
