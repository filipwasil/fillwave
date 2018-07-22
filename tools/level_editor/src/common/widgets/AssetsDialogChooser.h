#pragma once

#include <QDialog>
#include <QFileDialog>
#include <QDir>

namespace common {

class AssetsDialogChooser : public QObject {
 Q_OBJECT
 public:
  explicit AssetsDialogChooser(QObject* parent = Q_NULLPTR);

  ~AssetsDialogChooser() override;

  QString getAssetPath(QStringList typeList);

 public slots:

  void filterNavigation(const QString& directory);

 private:
  QString createDialog(QDir& folder);

  QFileDialog* mFileDialog;
};

}
