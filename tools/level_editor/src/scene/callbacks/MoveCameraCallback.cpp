#include "MoveCameraCallback.h"
#include <QEvent>
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

namespace flw {
namespace flf {

MoveCameraCallback::MoveCameraCallback(Engine *engine, EEventType eventType, float speed)
    : Callback(eventType), mSpeed(speed), mEngine(engine) {

}

void MoveCameraCallback::perform(EventType &event) {
  if (event.getType() == EEventType::eKey) {
    KeyboardEventData e = KeyboardEvent::getData(event);
    switch (e.key) {
      case Qt::Key_W:
        mEngine->getCurrentScene()->getCamera()->moveInDirection(glm::vec3(0.0, 0.0, -mSpeed));
        break;
      case Qt::Key_S:
        mEngine->getCurrentScene()->getCamera()->moveInDirection(glm::vec3(0.0, 0.0, mSpeed));
        break;
      case Qt::Key_D:
        if (e.action == QEvent::KeyRelease) {
          mEngine->configDebugger(EDebuggerState::eToggleState);
        }
        break;
    }
  } else if (event.getType() == EEventType::eCursorPosition) {
    static bool init = false;
    static int  a = 0;
    auto d = [](double value) {
      return static_cast<float>(value);
    };
    CursorPositionEventData e = CursorPositionEvent::getData(event);
    glm::ivec2 screenSize = mEngine->getScreenSize();
    double dx = e.xPosition - screenSize[0] / 2;
    double dy = screenSize[1] / 2 - e.yPosition;
    if (init) { /* debounce */
      mEngine->getCurrentScene()->getCamera()->rotateBy(glm::vec3(0.0f, 0.1f, 0.0f), -mSpeed * d(glm::radians(dx)));
      mEngine->getCurrentScene()->getCamera()->rotateBy(glm::vec3(1.0f, 0.0f, 0.0f), mSpeed * d(glm::radians(dy)));
      mEngine->getCurrentScene()->getCamera()->update();
    } else {
      init = true;
    }
  }
}

} /* framework */
} /* fillwave */
