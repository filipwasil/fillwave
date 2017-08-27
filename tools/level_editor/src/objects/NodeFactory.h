#pragma once

#include <QMap>
#include <QStandardItem>
#include "objects/INodeBase.h"
#include "common/ENodeType.hpp"
#include "INodeCreator.h"

namespace objects {

class NodeFactory {
 public:
  NodeFactory();

  INodeBase* createNode(common::ENodeType type, QString name, qintptr id);

  QStandardItem* createStandrdItem(common::ENodeType type, const QString& name);

 private:
  QMap<common::ENodeType, INodeCreator*> nodeCreators;
};
}

