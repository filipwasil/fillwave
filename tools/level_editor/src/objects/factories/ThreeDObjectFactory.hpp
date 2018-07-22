#pragma once

#include "objects/factories/IItemFactory.h"

namespace objects {
class ThreeDObjectFactory : public IItemFactory {
 public:
  BaseItem* create(common::EItemType type, QString& name, objects::BaseItem* parent
    , std::shared_ptr<flw::Engine> engine) override;

  std::unique_ptr<flw::flf::Model>
  initModel(const std::shared_ptr<Engine>& engine, flc::Program* program, const QString& fileName);
};
}
