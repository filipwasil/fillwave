#pragma once

#include <QList>
#include <QString>
#include <QVariant>
#include <fillwave/Fillwave.h>
#include "fillwave/models/Model.h"

using namespace flw;
using namespace flw::flf;

namespace objects {
class IItem {
 public:
  virtual ~IItem() = default;

  virtual IItem* parent() = 0;

  virtual QString name() const = 0;

  virtual QByteArray getId() const = 0;

  virtual void setName(const QString& name) = 0;

  virtual QList<IItem*> childrens() = 0;

  virtual IItem* childrenAt(int row) = 0;

  virtual void deleteChild(IItem* child) = 0;

  virtual bool hasChildren() = 0;

  virtual void swapChildren(int oldRow, int newRow) = 0;

  virtual IItem* takeChild(int row) = 0;

  virtual void setParent(IItem* parent) = 0;

  virtual int rowOfChild(IItem* child) = 0;

  virtual int row() const = 0;

  virtual int columnCount() const = 0;

  virtual QVariant data(int column) const = 0;

  virtual int childCount() const = 0;

  virtual bool operator== ( const IItem* obj ) const = 0;

  virtual void insertChild(int row, IItem *item) = 0;

  virtual void setId(QByteArray&& array) = 0;

  virtual void init() = 0;

  virtual void setEngine(std::shared_ptr<flw::Engine> engine) = 0;
};
}