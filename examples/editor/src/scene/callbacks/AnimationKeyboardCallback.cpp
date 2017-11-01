#include "AnimationKeyboardCallback.h"

namespace flw {
namespace flf {

AnimationKeyboardCallback::AnimationKeyboardCallback(Model* model)
    : mModel(model) {
}

AnimationKeyboardCallback::~AnimationKeyboardCallback() {
}

void AnimationKeyboardCallback::perform(const Event& event) {
  KeyboardEventData e = event.getData();
  if (mModel) {
    e.key;
    mModel->setActiveAnimation(e.key);
  }
}

} /* flf */
} /* flw */
