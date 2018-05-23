#include "TreeItemModel.h"
#include "QDebug"

namespace objects {

TreeItemModel::TreeItemModel(const QString& name, QObject* parent)
  : QAbstractItemModel(parent) {
  mRootItem = new objects::BaseItem(nullptr, QString("Root"), 0);
  mNewItemToInsert = nullptr;
}

TreeItemModel::~TreeItemModel() {
  delete mRootItem;
}

QVariant TreeItemModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }

  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  auto item = static_cast<IItem*>(index.internalPointer());

  return item->data(index.column());
}

Qt::ItemFlags TreeItemModel::flags(const QModelIndex& index) const {
  if (!index.isValid()) {
    return 0;
  }

  return QAbstractItemModel::flags(index);
}

QVariant TreeItemModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return mRootItem->data(section);
  }

  return QVariant();
}

QModelIndex TreeItemModel::index(int row, int column, const QModelIndex& parent) const {
  if (!hasIndex(row, column, parent)) {
    return QModelIndex();
  }

  IItem* parentItem;

  if (!parent.isValid()) {
    parentItem = mRootItem;
  } else {
    parentItem = static_cast<IItem*>(parent.internalPointer());
  }

  IItem* childItem = parentItem->childrenAt(row);
  if (childItem) {
    return createIndex(row, column, childItem);
  } else {
    return QModelIndex();
  }

}

QModelIndex TreeItemModel::parent(const QModelIndex& index) const {
  if (!index.isValid()) {
    return {};
  }

  auto childItem = static_cast<IItem*>(index.internalPointer());
  auto name = childItem->name().toStdString();
  IItem* parentItem = childItem->parent();

  if (parentItem == mRootItem) {
    return {
    };
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int TreeItemModel::rowCount(const QModelIndex& parent) const {
  if (parent.isValid() && parent.column() != 0) {
    return 0;
  }
  IItem* parentItem = itemForIndex(parent);
  return parentItem ? parentItem->childCount() : 0;
}

int TreeItemModel::columnCount(const QModelIndex& parent) const {
  if (parent.isValid()) {
    return static_cast<IItem*>(parent.internalPointer())->columnCount();
  } else {
    return mRootItem->columnCount();
  }
}

bool TreeItemModel::insertRows(int row, int count, const QModelIndex& parent) {
  if (count < 1 || row < 0) {
    return false;
  }
  if (!mRootItem) {
    mRootItem = new objects::BaseItem(nullptr, "Root", 0);
  }
  IItem* parentItem = parent.isValid() ? itemForIndex(parent) : mRootItem;
  beginInsertRows(parent, row, row + count - 1);
  for (int i = 0; i < count; ++i) {
    IItem* item = mNewItemToInsert ? mNewItemToInsert : new objects::BaseItem(parentItem, "StandardObject", 1);
    parentItem->insertChild(row, item);
  }
  endInsertRows();
  mNewItemToInsert = nullptr;
  return true;
}

IItem* TreeItemModel::itemForIndex(const QModelIndex& index) const {
  if (index.isValid()) {
    if (auto item = static_cast<IItem*>(
      index.internalPointer())) {
      return item;
    }
  }
  return mRootItem;
}

IItem* TreeItemModel::getRootItem() const {
  return mRootItem;
}

bool TreeItemModel::insertToModel(IItem* item) {
  mNewItemToInsert = item;
  return insertRow(1);
}

}