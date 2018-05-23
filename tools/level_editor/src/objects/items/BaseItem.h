#pragma once

#include "objects/IItem.h"

namespace objects {

class BaseItem : public IItem {
 public:
  BaseItem(IItem* parent, QString name, uint id);

  virtual ~BaseItem();

  IItem* parent() override;

  QString name() const override;

  void setName(const QString& name) override;

  QList<IItem*> childrens() override;

  IItem* childrenAt(int row) override;

  IItem* takeChild(int row) override;

  void deleteChild(IItem* child) override;

  void swapChildren(int oldRow, int newRow) override;

  bool hasChildren() override;

  uint getId() const override;

  int row() const override;

  void setParent(IItem* parent) override;

  int rowOfChild(IItem* child) override;

  int columnCount() const override;

  QVariant data(int column) const override;

  bool operator==(const IItem* obj) const override;

  int childCount() const override;

  void insertChild(int row, IItem* item) override;

 protected:
  IItem* mParent;
  QString mName;
  uint mId;
  QList<IItem*> mChildrens;
};
}

