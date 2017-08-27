#pragma once

#include <QStandardItemModel>

namespace common {
namespace operations {
class PrepareItemUniqueId {
 public:
  int operator()(QStandardItemModel* model);
};
}
}