#include <QLabel>
#include <QToolButton>
#include "MainWindowNodeOperations.h"

namespace common {
MainWindowNodeOperations::MainWindowNodeOperations(QWidget* parent)
  : mParent(parent)
  , QObject(parent) {

}

MainWindowNodeOperations::~MainWindowNodeOperations() {
  delete eventFilterMouse;
  eventFilterMouse = nullptr;
}

QVBoxLayout* MainWindowNodeOperations::createNodeWidget() {
  QLabel* label = new QLabel("Node", mParent);
  label->setAlignment(Qt::AlignHCenter);
  QToolButton* addNode = new QToolButton(mParent);
  addNode->setIcon(QIcon("icons/add.png"));
  QObject::connect(addNode, &QToolButton::clicked, this, &MainWindowNodeOperations::newNodeDialog);
  QToolButton* deleteNode = new QToolButton(mParent);
  deleteNode->setIcon(QIcon("icons/delete.png"));
  QHBoxLayout* hBox = new QHBoxLayout(mParent);
  hBox->addWidget(addNode);
  hBox->addWidget(deleteNode);
  mScenTree = new QTreeView(mParent);
  mScenTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mSceneModel = new QStandardItemModel(mParent);
  mScenTree->setModel(mSceneModel);
  QVBoxLayout* vBox = new QVBoxLayout(mParent);
  vBox->addWidget(label);
  vBox->addLayout(hBox);
  vBox->addWidget(mScenTree);
  eventFilterMouse = new scene::callbacks::StandardMouseEventHandler(mScenTree, this);
  mScenTree->viewport()->installEventFilter(eventFilterMouse);
  return vBox;
}

QVBoxLayout* MainWindowNodeOperations::createInspectorView() {
  QLabel* label = new QLabel("Inspector");
  label->setAlignment(Qt::AlignHCenter);

  QWidget* inspectorWidget = new QWidget(mParent);
  inspectorWidget->setLayout(new QVBoxLayout(inspectorWidget));
  auto mInspectorView2 = new QTableView();
  mInspectorView2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QVBoxLayout* vBox = new QVBoxLayout();
  mInspectorScrollArea = new QScrollArea(mParent);
  mInspectorScrollArea->setBackgroundRole(QPalette::Dark);
  mInspectorScrollArea->setWidget(inspectorWidget);
  vBox->addWidget(label);
  vBox->addWidget(mInspectorScrollArea);
  inspectorWidget->show();
  return vBox;
}

QVBoxLayout* MainWindowNodeOperations::createOther() {
  QLabel* label = new QLabel("Other", mParent);
  label->setAlignment(Qt::AlignHCenter);

  mOther = new QTreeWidget(mParent);
  mOther->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QVBoxLayout* vBox = new QVBoxLayout(mParent);
  vBox->addWidget(label);
  vBox->addWidget(mOther);
  return vBox;
}

void MainWindowNodeOperations::newNodeDialog() {
}

}