#ifndef TOOLS_H
#define TOOLS_H

#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QList>
#include <QWidget>
#include "common/ISceneController.h"

namespace tools {
    QVector<QString> readFileToStrings(QString pathToFile);
}

#endif
