#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>
#include "NodeFactory.h"
#include "objects/creators/SpriteCreator.h"

using namespace flw;
using namespace flw::flf;

namespace objects {
NodeFactory::NodeFactory(std::shared_ptr<flw::Engine> engine)
  : mEngine(engine) {
  nodeCreators[common::ENodeType::SPRITE] = new creators::SpriteCreator();
}

ANodeBase* NodeFactory::createNode(common::ENodeType type, QString name, qintptr id) {
  auto program = ProgramLoader(mEngine.get()).getProgram(EProgram::basic);
  // TODO: Na razie zabity testowy obiekt
  puModel ballModel1 = std::make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj");
  return (nodeCreators[type])->createCompleteNode(name, id);
}

}