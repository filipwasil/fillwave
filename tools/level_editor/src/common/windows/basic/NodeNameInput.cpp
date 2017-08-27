#include <QHBoxLayout>
#include <QVBoxLayout>
#include "NodeNameInput.h"

namespace common {
namespace windows {
namespace basic {

NodeNameInput::NodeNameInput(QWidget* parent)
  : QDialog(parent) {
  QHBoxLayout* buttons = new QHBoxLayout();
  mOk = new QPushButton("Ok");
  mCancel = new QPushButton("Cancel");
  buttons->addWidget(mOk);
  buttons->addWidget(mCancel);
  QVBoxLayout* all = new QVBoxLayout();
  mName = new QLineEdit();
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

NodeNameInput::~NodeNameInput() {
  delete mOk;
  delete mCancel;
  delete mName;
}
}
}
}