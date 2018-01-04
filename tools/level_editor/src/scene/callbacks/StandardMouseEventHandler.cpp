#include "StandardMouseEventHandler.h"
#include <QMouseEvent>

namespace scene {
namespace callbacks {

StandardMouseEventHandler::StandardMouseEventHandler(QTreeView* tree, QObject* parent)
  : QObject(parent)
  , mTree(tree) {
}

bool StandardMouseEventHandler::eventFilter(QObject* watched, QEvent* event) {
  if (event->type() != QEvent::MouseButtonRelease) {
    return QObject::eventFilter(watched, event);
  }
  QMouseEvent* mouse = dynamic_cast<QMouseEvent*>(event);
  if (!(mouse->button()) == Qt::LeftButton) {
    return QObject::eventFilter(watched, event);
  }
  QModelIndex item = mTree->indexAt(mouse->pos());
  bool selected = mTree->selectionModel()->isSelected(mTree->indexAt(mouse->pos()));

  if ((item.row() == -1 && item.column() == -1)) {
    mTree->clearSelection();
    const QModelIndex index;
    mTree->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
  }

}

}
}
