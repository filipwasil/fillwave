#include "memory"
#include "objects/factories/ItemFactory.h"
#include "ThreeDObjectFactory.hpp"

namespace objects {
ItemFactory::ItemFactory() {
  mFactories[common::EItemType::threeDObject] = std::make_unique<ThreeDObjectFactory>();
}

BaseItem* ItemFactory::create(common::EItemType type, QString& name, objects::BaseItem* parent,
  std::shared_ptr<flw::Engine> engine) {
  if (mFactories.count(type))
  {
    return mFactories[type]->create(type, name, parent, engine);
  }
  return nullptr;
}
}