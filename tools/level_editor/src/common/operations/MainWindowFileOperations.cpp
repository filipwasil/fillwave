#include "MainWindowFileOperations.h"
#include <QToolButton>
#include <QLabel>
#include <QFileSystemModel>

namespace common {
namespace operations {
MainWindowFileOperations::MainWindowFileOperations(QWidget* parent)
  : QObject(parent)
{
}

QVBoxLayout* MainWindowFileOperations::createFileSystemTree(QWidget* parent) {
  QLabel* label = new QLabel("File System", parent);
  label->setAlignment(Qt::AlignHCenter);
  QToolButton* addFolder = new QToolButton(parent);
  addFolder->setIcon(QIcon("icons/newFolder.jpg"));
  QToolButton* deleteFolder = new QToolButton(parent);
  deleteFolder->setIcon(QIcon("icons/delete.png"));
  QHBoxLayout* hBox = new QHBoxLayout();
  hBox->addWidget(addFolder);
  hBox->addWidget(deleteFolder);
  mFileSystemTree = new QTreeView(parent);
  mFileSystemTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QFileSystemModel* model = new QFileSystemModel(parent);
  model->setRootPath(QDir::currentPath());
  mFileSystemTree->setModel(model);
  mFileSystemTree->setRootIndex(model->index(QDir::currentPath()));
  mFileSystemTree->hideColumn(1);
  mFileSystemTree->hideColumn(2);
  mFileSystemTree->hideColumn(3);
  QVBoxLayout* vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addLayout(hBox);
  vBox->addWidget(mFileSystemTree);
  return vBox;
}

}
}