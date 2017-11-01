#include "SceneEventFactoryTest.h"

TEST_F(SceneEventFactoryTestFixture, testCreateDefualtKeyboardEvent
) {

auto keboardEvent = sut.getDefaultKeyboardData(0);
EXPECT_EQ(1, keboardEvent.action);
EXPECT_EQ(0, keboardEvent.key);
EXPECT_EQ(0, keboardEvent.mode);
EXPECT_EQ(0, keboardEvent.scanCode);
}

TEST_F(SceneEventFactoryTestFixture, testCreateKeyboardEvent
) {
auto keboardEvent = sut.getKeyboardData(0, 1, 2, 3);
EXPECT_EQ(0, keboardEvent.action);
EXPECT_EQ(1, keboardEvent.key);
EXPECT_EQ(2, keboardEvent.mode);
EXPECT_EQ(3, keboardEvent.scanCode);
}
