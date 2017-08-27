#pragma once

#include <QTreeView>
#include <QVBoxLayout>

namespace common {
namespace operations {

class MainWindowFileOperations : public QObject {
 public:
  MainWindowFileOperations(QObject* parent = nullptr);

  QVBoxLayout* createFileSystemTree();

 private:
  QTreeView* mFileSystemTree;
};

}
}

