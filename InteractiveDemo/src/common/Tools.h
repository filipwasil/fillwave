#pragma once

#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QList>
#include <QWidget>
#include <utility>

namespace tools {
QVector<QString> readFileToStrings(QString pathToFile);

QVector<std::pair<QString, QString>> readScenarioListWithPaths();

QVector<QString> readOnlyScenarioNames();
}

