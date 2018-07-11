#include "TreeItemModelFixture.hpp"

TEST_F(TreeItemModelFixture, insertingRow) {
  bool status = sut->insertRow(1);
  EXPECT_EQ(true, status);
}

TEST_F(TreeItemModelFixture, insertingRowChildAdded) {
  bool status = sut->insertRow(1);
  EXPECT_EQ(true, status);
  auto root = sut->getRootItem();
  EXPECT_EQ(true, root->hasChildren());
  auto child = root->childrenAt(0);
  auto parent = child->parent();
  EXPECT_EQ(parent, root);
}

TEST_F(TreeItemModelFixture, defaultItemCreationWithDefaultName) {
  bool status = sut->insertRow(1);
  EXPECT_EQ(true, status);
  QModelIndex invalidIndex;
  auto childIndex = sut->index(0, 0, invalidIndex);
  Q_ASSERT(childIndex.isValid());
  QVariant childNameData = sut->data(childIndex, Qt::DisplayRole);
  EXPECT_EQ(childNameData.isValid(), true);
  EXPECT_EQ(childNameData.toString(), "StandardObject");
}

TEST_F(TreeItemModelFixture, insertNewItemToModel) {
  QModelIndex model;
  bool status = sut->insertToModel(mTestItem, model);
  EXPECT_EQ(true, status);
  QModelIndex invalidIndex;
  auto childIndex = sut->index(0, 0, invalidIndex);
  Q_ASSERT(childIndex.isValid());
  QVariant childNameData = sut->data(childIndex, Qt::DisplayRole);
  EXPECT_EQ(childNameData.isValid(), true);
  EXPECT_EQ(childNameData.toString(), "TestObject");
}