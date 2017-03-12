#include "Tools.h"
#include <QMessageBox>

namespace tools {
QVector <QString> readFileToStrings(QString pathToFile) {
  QVector <QString> stringsVector;
  QFile inputFile(pathToFile);
  if (!inputFile.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox msgBox;
    msgBox.setText("Can't load file with resources for menu");
    msgBox.exec();
    return stringsVector;
  }
  QTextStream in(&inputFile);

  while (!in.atEnd()) {
    QString line = in.readLine();
    stringsVector.push_back(line);
  }
  inputFile.close();

  return stringsVector;
}
}

