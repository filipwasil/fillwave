#pragma once

#include <QWidget>

namespace loader {
class IWidgetFabric {
public:
  virtual ~IWidgetFabric() {

  }

  virtual QWidget *createWidget(QString typeName, QVector<std::pair<QString, QString>> &parametersVector) = 0;
};
}