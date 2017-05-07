#pragma once

#include <QWidget>
#include <QVector>
#include <utility>

namespace loader {
class IDataLoader {
public:
  virtual QList<QWidget *> load(QString pathToFile) = 0;
};
}