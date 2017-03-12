#ifndef CREATEMENUTEST_H
#define CREATEMENUTEST_H

#include <gtest/gtest.h>
#include "loader/MenuWidgetFabric.h"

class MenuWidgetsFabricTestFixture : public testing::Test
{
protected:
    virtual void SetUp() override {
        sut = new loader::MenuWidgetFabric();
    }

    virtual void TearDown() override {
        delete sut;
        sut = 0;
    }

    loader::MenuWidgetFabric *sut;
};

#endif // CREATEMENUTEST_H
