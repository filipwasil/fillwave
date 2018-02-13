#include "StandardMouseEventHandler.h"
#include <QMouseEvent>

namespace scene {
namespace callbacks {

StandardMouseEventHandler::StandardMouseEventHandler(const std::shared_ptr<flw::Engine> &engine)
    : mEngine(engine) {
}

void StandardMouseEventHandler::handle(QEvent *event) {
  if (event->type() == QEvent::MouseMove) {
    QMouseEvent *mouse = static_cast<QMouseEvent *>(event);
    if (!(mouse->buttons() & Qt::RightButton)) {
      return;
    }
    int x = mouse->x();
    int y = mouse->y();
    auto cursorData = mEventFactory.getCursorPositionData(x, y);
    flw::flf::Event lEvent(flw::flf::EEventType::cursorPosition,cursorData);
    mEngine->onEvent(lEvent);
  }
}

}
}
