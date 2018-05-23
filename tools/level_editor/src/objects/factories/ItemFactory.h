#pragma once

#include "objects/factories/IItemFactory.h"

namespace objects {
class ItemFactory : public IItemFactory {
 public:
  BaseItem* create(common::EItemType type, QString& name, objects::BaseItem* parent) override;
};
};