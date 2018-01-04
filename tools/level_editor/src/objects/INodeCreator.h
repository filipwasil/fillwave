#pragma once

#include "common/ENodeType.hpp"
#include "ANodeBase.h"

namespace objects {

class INodeCreator {
 public:
  virtual ~INodeCreator() = default;

  virtual ANodeBase* createCompleteNode(QString& name, qintptr id) = 0;
};
}