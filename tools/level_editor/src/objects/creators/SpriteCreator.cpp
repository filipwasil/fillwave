#include <QIcon>
#include "SpriteCreator.h"
#include "objects/standard/Sprite.h"

namespace objects {
namespace creators {

ANodeBase* SpriteCreator::createCompleteNode(QString& name, qintptr id) {
  //TODO: ID generator
  auto newSprite = new standard::Sprite(0, nullptr, nullptr);
  return newSprite;
}
}
}