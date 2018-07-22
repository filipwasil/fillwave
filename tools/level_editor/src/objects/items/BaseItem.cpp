#include <QtAlgorithms>
#include "BaseItem.h"

namespace objects {
BaseItem::BaseItem(IItem* parent, QString name)
  : mParent(parent)
  , mName(name) {

}

BaseItem::BaseItem(IItem* parent, QString name, QByteArray id)
  : mParent(parent)
  , mName(name)
  , mId(id) {
}

BaseItem::~BaseItem() {
  qDeleteAll(mChildrens);
}

IItem* BaseItem::parent() {
  return mParent;
}

QString BaseItem::name() const {
  return mName;
}

void BaseItem::setName(const QString& name) {
  mName = name;
}

QList<IItem*> BaseItem::childrens() {
  return mChildrens;
}

IItem* BaseItem::childrenAt(int row) {
  if (row > mChildrens.size()) {
    return nullptr;
  }
  return mChildrens.at(row);
}

void BaseItem::deleteChild(IItem* child) {
  auto index = mChildrens.indexOf(child);
  if (index == -1) {
    return;
  }
  mChildrens.removeAt(index);
  delete child;
  child = nullptr;
}

bool BaseItem::hasChildren() {
  return !mChildrens.empty();
}

QByteArray BaseItem::getId() const {
  return mId;
}

bool BaseItem::operator==(const IItem* obj) const {
  return this->mId == obj->getId();
}

void BaseItem::swapChildren(int oldRow, int newRow) {
  mChildrens.swap(oldRow, newRow);
}

IItem* BaseItem::takeChild(int row) {
  auto item = mChildrens.takeAt(row);
  Q_ASSERT(item);
  item->setParent(nullptr);
  return item;
}

int BaseItem::childCount() const {
  return mChildrens.count();
}

void BaseItem::setParent(IItem* parent) {
  mParent = parent;
}

int objects::BaseItem::rowOfChild(objects::IItem* child) {
  return mChildrens.indexOf(child);
}

int BaseItem::row() const {
  if (mParent) {
    return mParent->rowOfChild(const_cast<BaseItem*>(this));
  }
  return 0;
}

int BaseItem::columnCount() const {
  return 1;
}

QVariant BaseItem::data(int column) const {
  return mName;
}

void BaseItem::insertChild(int row, IItem* item) {
  item->setParent(this);
  mChildrens.insert(row, item);
}

void BaseItem::setId(QByteArray&& array) {
  mId = array;
}

void BaseItem::init() {
// empty
}

void BaseItem::setEngine(std::shared_ptr<flw::Engine> engine) {
  mEngine = engine;
}

}