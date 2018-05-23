#include "objects/factories/ItemFactory.h"

objects::BaseItem* objects::ItemFactory::create(common::EItemType type, QString& name, objects::BaseItem* parent) {
  return new objects::BaseItem(parent, name, 0);
}
