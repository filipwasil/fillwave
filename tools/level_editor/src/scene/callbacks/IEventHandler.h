#pragma once

#include <QtCore/QEvent>

namespace scene {
namespace callbacks {

class IEventHandler {
public:
  virtual ~IEventHandler() = default;

  virtual void handle(QEvent *event) = 0;

};
}
}