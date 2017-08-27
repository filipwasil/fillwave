#include <QIcon>
#include <QStandardItem>
#include "SpriteCreator.h"
#include "objects/standard/Sprite.h"
#include "common/InternalConsts.h"

namespace objects {
namespace creators {

INodeBase* SpriteCreator::createCompleteNode(QString& name, qintptr id) {
  //TODO: ID generator
  auto newSprite = new standard::Sprite(0, nullptr);
  return newSprite;
}
}
}