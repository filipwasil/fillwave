#include "NodeControllerFixture.h"

TEST_F(NodeControllerFixture, insertingRow) {
  EXPECT_CALL(*mTreeModelMock, insertToModel(testing::_)).WillOnce(testing::Return(true));
  auto addResult = sut->addNode(common::EItemType::Object, "Test");
  EXPECT_EQ(addResult, true);
}