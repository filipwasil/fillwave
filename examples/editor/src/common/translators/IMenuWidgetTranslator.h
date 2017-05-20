#pragma once

#include <QObject>
#include <QVariant>
#include <utility>

namespace common {
namespace translators {
class IMenuWidgetTranslator : public QObject {
Q_OBJECT
public:
  virtual ~IMenuWidgetTranslator() {
  }
  virtual void update() = 0;

  virtual std::pair<QString, QVariant> getCurrentValues() = 0;

signals :

  void updateScene(std::pair<QString, QVariant> menuElement);
};
}
}
