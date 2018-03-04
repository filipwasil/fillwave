#pragma once

#include <QTreeView>
#include <QVBoxLayout>

namespace common {
namespace operations {

class MainWindowFileOperations : public QObject {
 public:
  explicit MainWindowFileOperations(QWidget* parent = nullptr);

  QVBoxLayout* createFileSystemTree();

 private:
  QWidget* mParent;
  QTreeView* mFileSystemTree;
};

}
}

