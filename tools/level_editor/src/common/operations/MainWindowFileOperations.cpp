#include "MainWindowFileOperations.h"
#include <QToolButton>
#include <QLabel>
#include <QFileSystemModel>

namespace common {
namespace operations {

QVBoxLayout* MainWindowFileOperations::createFileSystemTree() {
  QLabel* label = new QLabel("File System");
  label->setAlignment(Qt::AlignHCenter);
  QToolButton* addFolder = new QToolButton();
  addFolder->setIcon(QIcon("icons/newFolder.jpg"));
  QToolButton* deleteFolder = new QToolButton();
  deleteFolder->setIcon(QIcon("icons/delete.png"));
  QHBoxLayout* hBox = new QHBoxLayout();
  hBox->addWidget(addFolder);
  hBox->addWidget(deleteFolder);
  mFileSystemTree = new QTreeView();
  mFileSystemTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QFileSystemModel* model = new QFileSystemModel;
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


MainWindowFileOperations::MainWindowFileOperations(QObject* parent)
  : QObject(parent) {
}
}
}