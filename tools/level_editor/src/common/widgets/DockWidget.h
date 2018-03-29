#pragma once

#include <QDockWidget>
#include <QCloseEvent>

namespace common {
namespace widgets {
class DockWidget : public QDockWidget {
 Q_OBJECT
 public:
  explicit DockWidget(const QString& title, QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

 protected:
  void closeEvent(QCloseEvent* event);
};
}
}


