#include <QIcon>
#include <QFileDialog>
#include <QObject>
#include "SpriteCreator.h"
#include "objects/standard/Sprite.h"
#include "common/windows/basic/AssetsDialogChooser.h"

using namespace flw;
using namespace flw::flf;

namespace objects {
namespace creators {

ANodeBase* SpriteCreator::createCompleteNode(QString& name, qintptr id, std::shared_ptr<flw::Engine> engine) {
  //TODO: ID generator
  auto program = ProgramLoader(engine.get()).getProgram(EProgram::basic);
  common::windows::basic::AssetsDialogChooser chooseAsset;
  QString fileName = chooseAsset.getAssetPath(QStringList("*.obj"));
  if (fileName.isEmpty()) {
    return nullptr;
  }
  auto ballModel1 = new Model(engine.get(), program, fileName.toStdString());
  // TODO: magic numbers
  ballModel1->scaleTo(0.1);
  ballModel1->moveBy(glm::vec3(-3.0, 0.0, 0.0));
  auto newSprite = new standard::Sprite(0, ballModel1, nullptr);
  return newSprite;
}
}
}