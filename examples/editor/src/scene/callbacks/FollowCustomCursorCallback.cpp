#include "FollowCustomCursorCallback.h"

namespace flw {
namespace flf {

FollowCustomCursorCallback::FollowCustomCursorCallback(Engine* engine)
  : mEngine(engine) {

}

void FollowCustomCursorCallback::perform(const Event& event) {

  CursorPositionEventData e = event.getData().mCursorPosition;
  auto xPosition = ((
                      e.xPosition / mEngine->getScreenSize()[0]
                    ) * 2.0 - 1.0
                   ) * 0.1;
  auto yPosition = (-(e.yPosition / mEngine->getScreenSize()[1]) * 2.0 + 1.0) * 0.5;
  mEngine->getCurrentScene()->getCamera()->moveByX(xPosition);
  mEngine->getCurrentScene()->getCamera()->moveByY(yPosition);
}

} /* framework */
} /* fillwave */
