#include <QKeyEvent>
#include "StandardKeyboardEventHandler.h"

namespace scene {
namespace callbacks {
StandardKeyboardEventHandler::StandardKeyboardEventHandler(const std::shared_ptr<flw::Engine> &engine)
    : mEngine(engine) {
}

void StandardKeyboardEventHandler::handle(QEvent *event) {
 /* if (event->type() == QEvent::KeyPress) {
    QKeyEvent *ke = static_cast<QKeyEvent *>(event);
    flw::flf::KeyboardEventData data = mEventFactory.getKeyboardEvent(QEvent::KeyPress, ke->key(), 0, 0);
    flw::flf::KeyboardEvent lEvent(data);
    mEngine->insertInput(lEvent);
  } else if (event->type() == QEvent::KeyRelease) {
    QKeyEvent *ke = static_cast<QKeyEvent *>(event);
    flw::flf::KeyboardEventData data = mEventFactory.getKeyboardEvent(QEvent::KeyRelease, ke->key(), 0, 0);
    flw::flf::KeyboardEvent lEvent(data);
    mEngine->insertInput(lEvent);
  }*/
}
}
}

