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
    //auto cursorEvent = mEventFactory.getCursorPositionEvent(x, y);
    //mEngine->insertInput(cursorEvent);
  }
}

}
}
