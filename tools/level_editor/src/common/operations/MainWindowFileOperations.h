#pragma once

#include <QTreeView>
#include <QVBoxLayout>

namespace common {
namespace operations {

class MainWindowFileOperations {
 public:
  QVBoxLayout* createFileSystemTree(QWidget* parent);

 private:
  QTreeView* mFileSystemTree;
};

}
}

