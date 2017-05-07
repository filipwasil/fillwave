#pragma once

#include <memory>
#include <QWidget>
#include <QVector>
#include <memory>
#include "common/ISceneController.h"

namespace loader {
namespace factory {
class IMenuWidgetFactory /*: public QObject*/ {
public:
  virtual ~IMenuWidgetFactory() {

  }

  virtual QWidget *
  create(QVector<std::pair<QString, QString>> &parametersVector, std::shared_ptr<common::ISceneController> scene) = 0;
};
}
}