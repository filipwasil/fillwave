#pragma once

#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/events/TEvent.h>

namespace flw {
class Engine;
namespace flf {

class MoveCameraCallback: public Callback {
 private:
	float mSpeed;
	Engine* mEngine;
 public:
	MoveCameraCallback(
	   Engine* engine,
	   eEventType eventType,
	   float speed = 1.0);
	virtual ~MoveCameraCallback() = default;

	virtual void perform (EventType& event);
};

} /* flf */
} /* flw */
