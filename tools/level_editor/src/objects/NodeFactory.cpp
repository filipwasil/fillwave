#include <QtAlgorithms>
#include "NodeFactory.h"
#include "objects/creators/SpriteCreator.h"

namespace objects {
NodeFactory::NodeFactory(std::shared_ptr<flw::Engine> engine)
  : mEngine(engine) {
  nodeCreators[common::ENodeType::SPRITE] = new creators::SpriteCreator();
}

ANodeBase* NodeFactory::createNode(common::ENodeType type, QString name, qintptr id) {
  return (nodeCreators[type])->createCompleteNode(name, id, mEngine);
}

NodeFactory::~NodeFactory() {
  qDeleteAll(nodeCreators);
}

}