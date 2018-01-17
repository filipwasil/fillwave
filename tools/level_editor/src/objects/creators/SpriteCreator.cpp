#include <QIcon>
#include "SpriteCreator.h"
#include "objects/standard/Sprite.h"

using namespace flw;
using namespace flw::flf;

namespace objects {
namespace creators {

ANodeBase* SpriteCreator::createCompleteNode(QString& name, qintptr id, std::shared_ptr<flw::Engine> engine) {
  //TODO: ID generator
  auto program = ProgramLoader(engine.get()).getProgram(EProgram::basic);
  // TODO: Na razie zabity testowy obiekt
  auto ballModel1 = new Model(engine.get(), program, "meshes/sphere.obj");
  ballModel1->scaleTo(0.1);
  ballModel1->moveBy(glm::vec3(-3.0, 0.0, 0.0));
  auto newSprite = new standard::Sprite(0, ballModel1, nullptr);
  return newSprite;
}
}
}