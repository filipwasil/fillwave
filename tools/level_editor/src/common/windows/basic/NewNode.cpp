#include <QtWidgets/QWidget>
#include <QVBoxLayout>
#include "common/windows/basic/NodeNameInput.h"
#include "NewNode.h"


namespace common {
namespace windows {
namespace basic {
NewNode::NewNode(QWidget* parent)
  : QDialog(parent)
  , mNodeModel(new QStandardItemModel())
  , mNodeList(new QTreeView())
  , mOk(new QPushButton("OK"))
  , mCancel(new QPushButton("Cancel")) {
  mTypeMap["Sprite"] = ENodeType::SPRITE;
  mSelectedNode = ENodeType::NONE;
  init();
  QVBoxLayout* mainLayout = new QVBoxLayout();
  mainLayout->addWidget(mNodeList);
  QHBoxLayout* buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(mOk);
  buttonLayout->addWidget(mCancel);
  mainLayout->addLayout(buttonLayout);
  this->setLayout(mainLayout);

  QObject::connect(mOk, &QPushButton::clicked, this, &NewNode::setNodeData);
  QObject::connect(mCancel, &QPushButton::clicked, this, &NewNode::close);
}

void NewNode::init() {
  QStandardItemModel* model = new QStandardItemModel();
  QStandardItem* item = new QStandardItem(QString("Sprite"));
  model->setItem(0, 0, item);
  mNodeList->setModel(model);
}

void NewNode::setNodeData() {
  NodeNameInput newName(this);
  newName.exec();
  mName = newName.getName();
  QModelIndex index = mNodeList->currentIndex();
  QVariant data = mNodeList->model()->data(index);
  QString text = data.toString();
  if (mTypeMap.contains(text)) {
    mSelectedNode = mTypeMap[text];
    this->close();
    return;
  }
  mSelectedNode = ENodeType::NONE;
  this->close();
}

ENodeType NewNode::getSelectedNode() const {
  return mSelectedNode;
}

const QString& NewNode::getName() const {
  return mName;
}

}
}
}