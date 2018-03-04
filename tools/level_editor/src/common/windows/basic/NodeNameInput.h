#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

namespace common {
namespace windows {
namespace basic {

class NodeNameInput : public QDialog {
 public:
  NodeNameInput(QWidget* parent = nullptr);

  QString getName();

 private:
  QPushButton* mOk;
  QPushButton* mCancel;
  QLineEdit* mName;
};
}
}
}

