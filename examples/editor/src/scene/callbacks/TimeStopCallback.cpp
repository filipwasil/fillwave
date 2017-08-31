#include "TimeStopCallback.h"
#include <QEvent>
#include <fillwave/Fillwave.h>

namespace flw {
namespace flf {

TimeStopCallback::TimeStopCallback(Engine *engine)
    : Callback(EEventType::eKey), mTimeOn(GL_TRUE), mEngine(engine) {

}

TimeStopCallback::~TimeStopCallback() {

}

void TimeStopCallback::perform(EventType &event) {
  KeyboardEventData data = KeyboardEvent::getData(event);
  /* You can handle Your callback directly here ... */
  if (data.key == Qt::Key_T && data.action == QEvent::KeyPress) {
    if (mTimeOn) {
      mTimeOn = false;
      mEngine->configTime(0.0);
    } else {
      mTimeOn = true;
      mEngine->configTime(1.0);
    }
  }
}

} /* actions */
} /* fillwave */
