#include "AssetsDialogChooser.h"
#include <QtCore>

namespace common {

AssetsDialogChooser::AssetsDialogChooser(QObject* parent)
  : QObject(parent)
  , mFileDialog(new QFileDialog()) {
  mFileDialog->setFileMode(QFileDialog::ExistingFile);
}

AssetsDialogChooser::~AssetsDialogChooser() {
  delete mFileDialog;
}

QString AssetsDialogChooser::getAssetPath(QStringList typeList) {
  QString mainDir = QCoreApplication::applicationDirPath();
  QDir dir(mainDir);
  dir.entryInfoList(typeList);
  return createDialog(dir);
}

QString AssetsDialogChooser::createDialog(QDir& folder) {
  mFileDialog->setDirectory(folder);
  QObject::connect(mFileDialog, &QFileDialog::directoryEntered, this, &AssetsDialogChooser::filterNavigation);
  auto status = mFileDialog->exec();
  if (QDialog::Accepted == status) {
    auto selected = mFileDialog->selectedFiles();
    auto path = folder.relativeFilePath(selected[0]);
    return path;
  }
  QString tmp = "";
  return tmp;
}

void AssetsDialogChooser::filterNavigation(const QString& directory) {
  QString mainDir = QCoreApplication::applicationDirPath();
  bool isOk = directory.contains(mainDir);
  if (!isOk) {
    mFileDialog->setDirectory(mainDir);
  }
}

}