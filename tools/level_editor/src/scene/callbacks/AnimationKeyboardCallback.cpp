#include "AnimationKeyboardCallback.h"

namespace flw {
namespace flf {

AnimationKeyboardCallback::AnimationKeyboardCallback(Entity* entity)
  : mEntity(entity) {
}

AnimationKeyboardCallback::~AnimationKeyboardCallback() = default;

void AnimationKeyboardCallback::perform(const Event& event) {
  KeyboardEventData e = event.getData();
  if (mEntity) {
    auto* model = dynamic_cast<Model*>(mEntity);
  }
}

} /* flf */
} /* flw */
