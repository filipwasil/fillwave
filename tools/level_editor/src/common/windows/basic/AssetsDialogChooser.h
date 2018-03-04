#pragma once

#include <QDialog>
#include <QFileDialog>
#include <QDir>

namespace common {
namespace windows {
namespace basic {

class AssetsDialogChooser : public QObject {
 Q_OBJECT
 public:
  explicit AssetsDialogChooser(QObject* parent = Q_NULLPTR);

  virtual ~AssetsDialogChooser();

  QString getAssetPath(QStringList typeList);

 public slots:

  void filterNavigation(const QString& directory);

 private:
  QString createDialog(QDir& folder);

  QFileDialog* mFileDialog;
};

}
}
}