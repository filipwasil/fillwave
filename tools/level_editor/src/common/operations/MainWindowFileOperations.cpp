#include "MainWindowFileOperations.h"
#include <QToolButton>
#include <QLabel>
#include <QFileSystemModel>

namespace common {
namespace operations {
MainWindowFileOperations::MainWindowFileOperations(QWidget* parent)
  : QObject(parent),
    mParent(parent)
{
}

QVBoxLayout* MainWindowFileOperations::createFileSystemTree() {
  QLabel* label = new QLabel("File System", mParent);
  label->setAlignment(Qt::AlignHCenter);
  QToolButton* addFolder = new QToolButton(mParent);
  addFolder->setIcon(QIcon("icons/newFolder.jpg"));
  QToolButton* deleteFolder = new QToolButton(mParent);
  deleteFolder->setIcon(QIcon("icons/delete.png"));
  QHBoxLayout* hBox = new QHBoxLayout(mParent);
  hBox->addWidget(addFolder);
  hBox->addWidget(deleteFolder);
  mFileSystemTree = new QTreeView(mParent);
  mFileSystemTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QFileSystemModel* model = new QFileSystemModel(mParent);
  model->setRootPath(QDir::currentPath());
  mFileSystemTree->setModel(model);
  mFileSystemTree->setRootIndex(model->index(QDir::currentPath()));
  mFileSystemTree->hideColumn(1);
  mFileSystemTree->hideColumn(2);
  mFileSystemTree->hideColumn(3);
  QVBoxLayout* vBox = new QVBoxLayout(mParent);
  vBox->addWidget(label);
  vBox->addLayout(hBox);
  vBox->addWidget(mFileSystemTree);
  return vBox;
}

}
}