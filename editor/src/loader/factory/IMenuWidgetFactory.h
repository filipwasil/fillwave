#pragma once

#include <QWidget>
#include <QVector>
#include "common/ISceneController.h"

namespace loader {
namespace factory {
class IMenuWidgetFactory /*: public QObject*/ {
public:
  virtual ~IMenuWidgetFactory() {

  }

  virtual QWidget *create(QVector <std::pair<QString, QString>> &parametersVector, common::ISceneController *scene) = 0;
};
}
}