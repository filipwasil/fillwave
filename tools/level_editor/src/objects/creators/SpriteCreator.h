#pragma once

#include "objects/INodeCreator.h"

namespace objects {
namespace creators {
class SpriteCreator : public INodeCreator {
 public:
  ANodeBase* createCompleteNode(QString& name, qintptr id, std::shared_ptr<flw::Engine> engine) override;
};
}
}
