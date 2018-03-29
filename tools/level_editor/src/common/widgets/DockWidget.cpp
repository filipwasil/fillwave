#include "DockWidget.h"

namespace common {
namespace widgets {
DockWidget::DockWidget(const QString& title, QWidget* parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags) {
}

void DockWidget::closeEvent(QCloseEvent* event) {
  this->hide();
}

}
}