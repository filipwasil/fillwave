#pragma once
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>
#include "common/ENodeType.hpp"
#include "ANodeBase.h"

namespace objects {

class INodeCreator {
 public:
  virtual ~INodeCreator() = default;

  virtual ANodeBase* createCompleteNode(QString& name, qintptr id, std::shared_ptr<flw::Engine> engine) = 0;
};
}