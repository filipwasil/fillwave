#pragma once
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

namespace flw {
class Engine;
namespace flf {

/*! \class AnimationKeyboardCallback
 *
 * \brief EngineCallback to change current animation.
 *
 * This callback, when attached to a model, can change
 * the current active animation.
 *
 */

class AnimationKeyboardCallback : public Callback {
public:
  AnimationKeyboardCallback(Entity *entity, eEventType eventType);

  virtual ~AnimationKeyboardCallback();

  void perform(EventType &event);

private:
  Entity *mEntity;
};
} /* flf */
} /* flw */
