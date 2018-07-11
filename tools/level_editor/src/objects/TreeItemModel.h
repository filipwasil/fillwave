#pragma once

#include <QAbstractItemModel>
#include "objects/items/BaseItem.h"

namespace objects {
class TreeItemModel : public QAbstractItemModel {
 Q_OBJECT
 public:
  explicit TreeItemModel(const QString& name, QObject* parent = Q_NULLPTR);

  virtual ~TreeItemModel();

  QVariant data(const QModelIndex& index, int role) const override;

  Qt::ItemFlags flags(const QModelIndex& index) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

  QModelIndex parent(const QModelIndex& index) const override;

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  int columnCount(const QModelIndex& parent = QModelIndex()) const override;

  IItem* itemForIndex(const QModelIndex& index) const;

  IItem* getRootItem() const;

  virtual bool insertToModel(IItem* item, const QModelIndex& parent);

 private:
  bool insertRows(int row, int count, const QModelIndex& parent) override;

 private:
  IItem* mRootItem;
  IItem* mNewItemToInsert;
};
}
