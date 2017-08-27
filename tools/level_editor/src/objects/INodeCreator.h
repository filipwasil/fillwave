#pragma once

#include "common/ENodeType.hpp"
#include "INodeBase.h"

namespace objects {

class INodeCreator {
 public:
  virtual ~INodeCreator() = default;

  virtual INodeBase* createCompleteNode(QString& name, qintptr id) = 0;
};
}