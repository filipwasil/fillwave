#include <QLabel>
#include <QToolButton>
#include <QIcon>
#include "MainWindowNodeOperations.h"
#include "common/ENodeType.hpp"
#include "common/windows/basic/NewNode.h"
#include "objects/NodeFactory.h"
#include "common/InternalConsts.h"

namespace common {
MainWindowNodeOperations::MainWindowNodeOperations(QObject* parent)
  : QObject(parent) {

}

MainWindowNodeOperations::~MainWindowNodeOperations() {
  delete eventFilterMouse;
  eventFilterMouse = nullptr;
}

QVBoxLayout* MainWindowNodeOperations::createNodeWidget() {
  QLabel* label = new QLabel("Node");
  label->setAlignment(Qt::AlignHCenter);
  QToolButton* addNode = new QToolButton();
  addNode->setIcon(QIcon("icons/add.png"));
  QObject::connect(addNode, &QToolButton::clicked, this, &MainWindowNodeOperations::newNodeDailog);
  QToolButton* deleteNode = new QToolButton();
  deleteNode->setIcon(QIcon("icons/delete.png"));
  QHBoxLayout* hBox = new QHBoxLayout();
  hBox->addWidget(addNode);
  hBox->addWidget(deleteNode);
  mScenTree = new QTreeView();
  mScenTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mSceneModel = new QStandardItemModel();
  mScenTree->setModel(mSceneModel);
  QVBoxLayout* vBox = new QVBoxLayout();
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

  mInspectorView = new QTableView();
  mInspectorView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QVBoxLayout* vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addWidget(mInspectorView);
  return vBox;
}

QVBoxLayout* MainWindowNodeOperations::createOther() {
  QLabel* label = new QLabel("Other");
  label->setAlignment(Qt::AlignHCenter);

  mOther = new QTreeWidget();
  mOther->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QVBoxLayout* vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addWidget(mOther);
  return vBox;
}

void MainWindowNodeOperations::newNodeDailog() {
  common::windows::basic::NewNode sNode;
  sNode.exec();
  auto nodeType = sNode.getSelectedNode();
  if (nodeType == ENodeType::NONE) {
    return;
  }
  objects::NodeFactory nFactory;
  QModelIndex idx = mScenTree->currentIndex();
  auto item = mSceneModel->itemFromIndex(idx);
  auto newItem = nFactory.createStandrdItem(nodeType, sNode.getName());
  if (item) {
    item->setChild(item->rowCount(), newItem);
  } else {
    mSceneModel->appendRow(newItem);
  }
  auto newItemModel = newItem->index();
  auto readyNode = nFactory.createNode(nodeType, sNode.getName(), newItemModel.internalId());

}

}