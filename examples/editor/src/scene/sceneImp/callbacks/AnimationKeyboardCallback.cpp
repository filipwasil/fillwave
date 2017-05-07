#include "AnimationKeyboardCallback.h"

namespace flw {
namespace flf {

AnimationKeyboardCallback::AnimationKeyboardCallback(Entity *entity, eEventType EventType)
    : Callback(EventType), mEntity(entity) {
}

AnimationKeyboardCallback::~AnimationKeyboardCallback() {
}

void AnimationKeyboardCallback::perform(EventType & event) {
  KeyboardEventData e = KeyboardEvent::getData(event);
  if (mEntity) {
    Model *model = static_cast<Model *>(mEntity);
  }
}

} /* flf */
} /* flw */
