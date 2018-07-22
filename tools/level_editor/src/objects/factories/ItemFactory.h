#pragma once

#include "objects/factories/IItemFactory.h"

namespace objects {

class ItemFactory : public IItemFactory {
 public:
  ItemFactory();

  BaseItem*
  create(common::EItemType type, QString& name, objects::BaseItem* parent, std::shared_ptr<flw::Engine> engine) override;

 private:
  std::map<common::EItemType, std::unique_ptr<IItemFactory>> mFactories;
};
};