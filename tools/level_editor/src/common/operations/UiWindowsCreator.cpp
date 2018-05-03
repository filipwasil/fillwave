#include <QLabel>
#include <QToolButton>
#include "UiWindowsCreator.h"
#include "objects/TreeItemModel.h"

namespace common {
UiWindowsCreator::UiWindowsCreator(QWidget* parent)
  : QObject(parent) {

}

UiWindowsCreator::~UiWindowsCreator() {
  // TODO: New memory magnamet for eventMouse
}

QVBoxLayout* UiWindowsCreator::createNodeLayout(QTreeView* treeView, QWidget* parent) {
  QLabel* label = new QLabel("Node", parent);
  label->setAlignment(Qt::AlignHCenter);
  auto addNode = new QToolButton(parent);
  addNode->setIcon(QIcon("icons/add.png"));
  auto deleteNode = new QToolButton(parent);
  deleteNode->setIcon(QIcon("icons/delete.png"));
  auto hBox = new QHBoxLayout();
  hBox->addWidget(addNode);
  hBox->addWidget(deleteNode);
  treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  objects::TreeItemModel* model = new objects::TreeItemModel("InspectorModel", nullptr);
  treeView->setModel(model);
  auto vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addLayout(hBox);
  vBox->addWidget(treeView);
  return vBox;
}

scene::callbacks::StandardMouseEventHandler*
UiWindowsCreator::installEventFilterOnTreeView(QTreeView* treeView, QWidget* parent) {
  auto eventFilterMouse = new scene::callbacks::StandardMouseEventHandler(treeView, parent);
  treeView->viewport()->installEventFilter(eventFilterMouse);
  return eventFilterMouse;
}

QVBoxLayout* UiWindowsCreator::createInspectorViewLayout(QScrollArea* inspectorArea, QWidget* parent) {
  QLabel* label = new QLabel("Inspector", parent);
  label->setAlignment(Qt::AlignHCenter);
  QWidget* inspectorWidget = new QWidget(inspectorArea);
  inspectorWidget->setLayout(new QVBoxLayout(inspectorWidget));
  auto vBox = new QVBoxLayout();
  inspectorArea->setBackgroundRole(QPalette::Dark);
  inspectorArea->setWidget(inspectorWidget);
  vBox->addWidget(label);
  vBox->addWidget(inspectorArea);
  inspectorWidget->show();
  return vBox;
}

QVBoxLayout* UiWindowsCreator::createObjectPropertiesLayout(QTreeView* propertiesTree, QWidget* parent) {
  auto label = new QLabel("Other", parent);
  label->setAlignment(Qt::AlignHCenter);
  propertiesTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  auto vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addWidget(propertiesTree);
  return vBox;
}

}