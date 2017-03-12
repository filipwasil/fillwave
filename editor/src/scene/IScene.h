#pragma once

#include <utility>
#include <QString>

namespace scene {
class IScene {
public:
  virtual void updateValue(const std::pair<QString, QString> &value) = 0;
};
}
