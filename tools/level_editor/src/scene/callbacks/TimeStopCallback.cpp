#include "TimeStopCallback.h"
#include <QEvent>
#include <flw/Fillwave.h>

namespace flw {
namespace flf {

TimeStopCallback::TimeStopCallback(Engine* engine)
  : mTimeOn(GL_TRUE)
  , mEngine(engine) {

}

TimeStopCallback::~TimeStopCallback() = default;

void TimeStopCallback::perform(const Event& event) {
  KeyboardEventData data = event.getData();
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
