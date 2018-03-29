#include <QFileSystemModel>
#include <QToolButton>
#include <QLabel>
#include "MainWindowFileOperations.h"

namespace common {
namespace operations {

QVBoxLayout* MainWindowFileOperations::createFileSystemTree(QWidget* parent) {
  QLabel* label = new QLabel("File System", parent);
  label->setAlignment(Qt::AlignHCenter);
  auto addFolder = new QToolButton(parent);
  addFolder->setIcon(QIcon("icons/newFolder.jpg"));
  auto deleteFolder = new QToolButton(parent);
  deleteFolder->setIcon(QIcon("icons/delete.png"));
  auto hBox = new QHBoxLayout();
  hBox->addWidget(addFolder);
  hBox->addWidget(deleteFolder);
  mFileSystemTree = new QTreeView(parent);
  mFileSystemTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  auto model = new QFileSystemModel(parent);
  model->setRootPath(QDir::currentPath());
  mFileSystemTree->setModel(model);
  mFileSystemTree->setRootIndex(model->index(QDir::currentPath()));
  mFileSystemTree->hideColumn(1);
  mFileSystemTree->hideColumn(2);
  mFileSystemTree->hideColumn(3);
  auto vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addLayout(hBox);
  vBox->addWidget(mFileSystemTree);
  return vBox;
}

}
}