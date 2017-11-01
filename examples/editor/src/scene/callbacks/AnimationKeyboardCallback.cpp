#include "AnimationKeyboardCallback.h"

namespace flw {
namespace flf {

AnimationKeyboardCallback::AnimationKeyboardCallback(Entity *entity)
    : mEntity(entity) {
}

AnimationKeyboardCallback::~AnimationKeyboardCallback() {
}

void AnimationKeyboardCallback::perform(const Event& event) {
  KeyboardEventData e = event.getData();
  if (mEntity) {
    Model *model = static_cast<Model *>(mEntity);
  }
}

} /* flf */
} /* flw */
