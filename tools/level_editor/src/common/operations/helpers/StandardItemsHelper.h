#pragma once

#include <QStandardItem>
#include "common/ENodeType.hpp"

namespace common {
namespace operations {
namespace helpers {

class StandardItemsHelper {
 public:
  QStandardItem* createStandardItem(common::ENodeType type, const QString& name);
};

}
}
}


