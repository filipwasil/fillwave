#ifndef CREATEMENUTEST_H
#define CREATEMENUTEST_H
#include <gtest/gtest.h>
#include "createmenuwidgets.h"

class CreateMenuWidgetsTest : public testing::Test
{
    virtual void SetUp() override
    {
        sut = new CreateScenerioMenu();
    }

    virtual void TearDown() override
    {
        delete sut;
        sut = 0;
    }
    sceneriocreation::CreateMenuWidgets* sut;
};

#endif // XMLLOADTEXT_H
