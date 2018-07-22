#pragma once

#include "objects/IItem.h"

namespace objects {

class BaseItem : public IItem {
 public:
  BaseItem(IItem* parent, QString name);

  BaseItem(IItem* parent, QString name, QByteArray id);

  virtual ~BaseItem();

  IItem* parent() override;

  QString name() const override;

  void init() override;

  void setName(const QString& name) override;

  QList<IItem*> childrens() override;

  IItem* childrenAt(int row) override;

  IItem* takeChild(int row) override;

  void deleteChild(IItem* child) override;

  void swapChildren(int oldRow, int newRow) override;

  bool hasChildren() override;

  QByteArray getId() const override;

  void setEngine(std::shared_ptr<flw::Engine> engine) override;

  int row() const override;

  void setId(QByteArray&& array) override;

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
  QByteArray mId;
  std::shared_ptr<flw::Engine> mEngine;
  QList<IItem*> mChildrens;
};
}

