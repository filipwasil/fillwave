#pragma once

#include <QTreeView>
//#include "common/SceneEventFactory.h"

namespace scene {
namespace callbacks {
class StandardMouseEventHandler : public QObject {
 public:
  explicit StandardMouseEventHandler(QTreeView* tree, QObject* parent = nullptr);

  bool eventFilter(QObject* watched, QEvent* event) override;

 private:
  QTreeView* mTree;
};

}
}

