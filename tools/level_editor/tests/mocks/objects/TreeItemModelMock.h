#pragma once

#include "gmock/gmock.h"
#include "objects/TreeItemModel.h"

namespace objects {
class TreeItemModelMock : public TreeItemModel {
 public:
  TreeItemModelMock()
    : TreeItemModel("Mock") {
  }

  MOCK_METHOD2(data, QVariant(
    const QModelIndex& index,
    int role));

  MOCK_METHOD1(flags, Qt::ItemFlags(
    const QModelIndex& index));

  MOCK_METHOD3(headerData, QVariant(int
    section, Qt::Orientation
    orientation, int
    role));

  MOCK_METHOD3(index, QModelIndex(int
    row, int
    column,
    const QModelIndex& parent));

  MOCK_METHOD1(parent, QModelIndex(
    const QModelIndex& index));

  MOCK_METHOD1(rowCount, int(
    const QModelIndex& index));

  MOCK_METHOD1(columnCount, int(
    const QModelIndex& index));

  MOCK_METHOD2(insertToModel, bool(
    IItem * item, const QModelIndex& parent));
};
}