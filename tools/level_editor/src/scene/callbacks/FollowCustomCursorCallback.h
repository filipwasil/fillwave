#pragma once

#include <fillwave/Framework.h>
#include <fillwave/Fillwave.h>

namespace flw {
class Engine;
namespace flf {

class FollowCustomCursorCallback: public Callback {
 public:
	FollowCustomCursorCallback(Engine* engine);
	virtual ~FollowCustomCursorCallback() = default;
	void perform (EventType& event);
 private:
	Engine* mEngine;
};

} /* flf */
} /* flw */
