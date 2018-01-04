#include "StandardItemsHelper.h"
#include "common/InternalConsts.h"

namespace common {
namespace operations {
namespace helpers {
QStandardItem* StandardItemsHelper::createStandardItem(common::ENodeType type, const QString& name) {
  QStandardItem* testItem = new QStandardItem(QIcon(SPRITE_ICON_PATH), name);
  return testItem;
}
}
}
}