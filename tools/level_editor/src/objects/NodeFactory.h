#pragma once

#include <QMap>
#include "objects/ANodeBase.h"
#include "common/ENodeType.hpp"
#include "INodeCreator.h"

namespace objects {

class NodeFactory {
 public:
  explicit NodeFactory(std::shared_ptr<flw::Engine> engine);

  ANodeBase* createNode(common::ENodeType type, QString name, qintptr id);

  virtual ~NodeFactory();

 private:
  std::shared_ptr<flw::Engine> mEngine;
  QMap<common::ENodeType, INodeCreator*> nodeCreators;
};
}

