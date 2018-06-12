#include <QFileSystemModel>
#include <QToolButton>
#include <QLabel>
#include "UiFilesWindowsCreator.h"

namespace common {

QVBoxLayout* UiFilesWindowsCreator::createFileSystemTree(QTreeView* treeFileView, QWidget* parent) {
  QLabel* label = new QLabel("File System", parent);
  label->setAlignment(Qt::AlignHCenter);
  auto* addFolder = new QToolButton(parent);
  addFolder->setIcon(QIcon("icons/newFolder.jpg"));
  auto* deleteFolder = new QToolButton(parent);
  deleteFolder->setIcon(QIcon("icons/delete.png"));
  auto* hBox = new QHBoxLayout();
  hBox->addWidget(addFolder);
  hBox->addWidget(deleteFolder);
  treeFileView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  auto* model = new QFileSystemModel(parent);
  model->setRootPath(QDir::currentPath());
  treeFileView->setModel(model);
  treeFileView->setRootIndex(model->index(QDir::currentPath()));
  treeFileView->hideColumn(1);
  treeFileView->hideColumn(2);
  treeFileView->hideColumn(3);
  auto* vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addLayout(hBox);
  vBox->addWidget(treeFileView);
  return vBox;
}

}