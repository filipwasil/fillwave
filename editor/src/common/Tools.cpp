#include "Tools.h"
#include <QMessageBox>

namespace tools {
QVector<QString> readFileToStrings(QString pathToFile) {
  QVector<QString> stringsVector;
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

QVector<std::pair<QString, QString>> readScenarioListWithPaths() {
  QFile inputFile("assets/ScenerioList.txt");
  QVector<std::pair<QString, QString>> scensList;
  if (!inputFile.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox msgBox;
    msgBox.setText("Can't load file with scenario list");
    msgBox.exec();
    return scensList;
  }
  QTextStream in(&inputFile);

  while (!in.atEnd()) {
    QString name = in.readLine();
    if (in.atEnd()) {
      continue;
    }
    QString path = in.readLine();
    scensList.push_back(std::make_pair(name, path));
  }
  inputFile.close();
  return scensList;
}

QVector<QString> readOnlyScenarioNames() {
  auto namesWithPaths = readScenarioListWithPaths();
  QVector<QString> names;
  for (auto &pair : namesWithPaths) {
    names.push_back(pair.first);
  }
  return names;
}

}

