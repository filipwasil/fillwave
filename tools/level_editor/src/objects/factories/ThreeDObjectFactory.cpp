#include "ThreeDObjectFactory.hpp"
#include "objects/items/ThreeDObject.h"
#include "common/widgets/AssetsDialogChooser.h"

using namespace flw;
using namespace flw::flf;

namespace objects {
BaseItem* ThreeDObjectFactory::create(common::EItemType type
  , QString& name
  , objects::BaseItem* parent
  , std::shared_ptr<flw::Engine> engine) {
  auto program = ProgramLoader(engine.get()).getProgram(EProgram::basic);
  common::AssetsDialogChooser chooseAsset;
  QString fileName = chooseAsset.getAssetPath(QStringList("*.obj"));
  if (fileName.isEmpty()) {
    return nullptr;
  }
  auto model = initModel(engine, program, fileName);
  auto newObject = new ThreeDObject(parent, name, 0, std::move(model));
  return newObject;
}

std::unique_ptr<flw::flf::Model> ThreeDObjectFactory::initModel(const std::shared_ptr<Engine>& engine
  , flc::Program* program
  , const QString& fileName) {
  auto model = std::make_unique<Model>(engine.get(), program, fileName.toStdString());
  model->scaleTo(0.1);
  model->moveBy(glm::vec3(-3.0, 0.0, 0.0));
  return std::move(model);
}
}