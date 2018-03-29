#include <QLabel>
#include <QToolButton>
#include "MainWindowNodeOperations.h"

namespace common {
MainWindowNodeOperations::MainWindowNodeOperations(QWidget* parent)
  : QObject(parent) {

}

MainWindowNodeOperations::~MainWindowNodeOperations() {
  delete eventFilterMouse;
  eventFilterMouse = nullptr;
}

QVBoxLayout* MainWindowNodeOperations::createNodeLayout(QWidget* parent) {
  QLabel* label = new QLabel("Node", parent);
  label->setAlignment(Qt::AlignHCenter);
  auto addNode = new QToolButton(parent);
  addNode->setIcon(QIcon("icons/add.png"));
  auto deleteNode = new QToolButton(parent);
  deleteNode->setIcon(QIcon("icons/delete.png"));
  auto hBox = new QHBoxLayout();
  hBox->addWidget(addNode);
  hBox->addWidget(deleteNode);
  auto nodeTree = new QTreeView(parent);
  nodeTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  auto sceneModel = new QStandardItemModel(parent);
  nodeTree->setModel(sceneModel);
  auto vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addLayout(hBox);
  vBox->addWidget(nodeTree);
  eventFilterMouse = new scene::callbacks::StandardMouseEventHandler(nodeTree, this);
  nodeTree->viewport()->installEventFilter(eventFilterMouse);
  return vBox;
}


QVBoxLayout* MainWindowNodeOperations::createInspectorViewLayout(QWidget* parent) {
  QLabel* label = new QLabel("Inspector", parent);
  label->setAlignment(Qt::AlignHCenter);
  QWidget* inspectorWidget = new QWidget(parent);
  inspectorWidget->setLayout(new QVBoxLayout(inspectorWidget));
  auto vBox = new QVBoxLayout();
  auto inspectorScrollArea = new QScrollArea(parent);
  inspectorScrollArea->setBackgroundRole(QPalette::Dark);
  inspectorScrollArea->setWidget(inspectorWidget);
  vBox->addWidget(label);
  vBox->addWidget(inspectorScrollArea);
  inspectorWidget->show();
  return vBox;
}

QVBoxLayout* MainWindowNodeOperations::createObjectPropertiesLayout(QWidget* parent) {
  auto label = new QLabel("Other", parent);
  label->setAlignment(Qt::AlignHCenter);
  auto other = new QTreeWidget(parent);
  other->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  auto vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addWidget(other);
  return vBox;
}

}