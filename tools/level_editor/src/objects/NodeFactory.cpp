#include "NodeFactory.h"
#include "objects/creators/SpriteCreator.h"
#include "common/InternalConsts.h"
#include "INodeBase.h"

namespace objects {
NodeFactory::NodeFactory() {
  nodeCreators[common::ENodeType::SPRITE] = new creators::SpriteCreator();
}

INodeBase* NodeFactory::createNode(common::ENodeType type, QString name, qintptr id) {
  return (nodeCreators[type])->createCompleteNode(name, id);
}

QStandardItem* NodeFactory::createStandrdItem(common::ENodeType type, const QString& name) {
  QStandardItem* testItem = new QStandardItem(QIcon(SPRITE_ICON_PATH), name);
  return testItem;
}

}