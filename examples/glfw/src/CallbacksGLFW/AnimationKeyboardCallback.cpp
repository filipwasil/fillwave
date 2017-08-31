#include "CallbacksGLFW/AnimationKeyboardCallback.h"

namespace flw {
namespace flf {

AnimationKeyboardCallback::AnimationKeyboardCallback(Entity *entity, EEventType EventType)
    : Callback(EventType), mEntity(entity) {
}

AnimationKeyboardCallback::~AnimationKeyboardCallback() {
}

void AnimationKeyboardCallback::perform(EventType & event) {
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  KeyboardEventData e = KeyboardEvent::getData(event);
  if (mEntity) {
    Model *model = static_cast<Model *>(mEntity);
    switch (e.key) {
      case GLFW_KEY_Q:
        model->setActiveAnimation(FILLWAVE_DO_NOT_ANIMATE);
        break;
      case GLFW_KEY_0:
        model->setActiveAnimation(0);
        break;
      case GLFW_KEY_1:
        model->setActiveAnimation(1);
        break;
      case GLFW_KEY_2:
        model->setActiveAnimation(2);
        break;
      case GLFW_KEY_3:
        model->setActiveAnimation(3);
        break;
      case GLFW_KEY_4:
        model->setActiveAnimation(4);
        break;
      case GLFW_KEY_5:
        model->setActiveAnimation(5);
        break;
      case GLFW_KEY_6:
        model->setActiveAnimation(6);
        break;
      case GLFW_KEY_7:
        model->setActiveAnimation(7);
        break;
      case GLFW_KEY_8:
        model->setActiveAnimation(8);
        break;
      case GLFW_KEY_9:
        model->setActiveAnimation(9);
        break;
      default:
        break;
    }
  }
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
}

} /* flf */
} /* flw */
