#pragma once

#include <QTreeView>
#include <QVBoxLayout>

namespace common {

class UiFilesWindowsCreator {
 public:
  QVBoxLayout* createFileSystemTree(QTreeView* treeView, QWidget* parent);
};

}

