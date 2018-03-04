#include <QHBoxLayout>
#include "NodeNameInput.h"

namespace common {
namespace windows {
namespace basic {

NodeNameInput::NodeNameInput(QWidget* parent)
  : QDialog(parent) {
  QHBoxLayout* buttons = new QHBoxLayout(this);
  mOk = new QPushButton("Ok", this);
  mCancel = new QPushButton("Cancel", this);
  buttons->addWidget(mOk);
  buttons->addWidget(mCancel);
  QVBoxLayout* all = new QVBoxLayout(this);
  mName = new QLineEdit(this);
  all->addWidget(mName);
  all->addLayout(buttons);
  QObject::connect(mOk, &QPushButton::clicked, this, &QDialog::close);
  QObject::connect(mCancel, &QPushButton::clicked, this, &QDialog::close);
  this->setMaximumSize(300, 200);
  this->setLayout(all);
}

QString NodeNameInput::getName() {
  return mName->text();
}

}
}
}