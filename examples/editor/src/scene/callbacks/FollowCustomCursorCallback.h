#pragma once

#include <fillwave/Framework.h>
#include <fillwave/Fillwave.h>

namespace flw {
class Engine;
namespace flf {

class FollowCustomCursorCallback {
 public:
	FollowCustomCursorCallback(Engine* engine);
	virtual ~FollowCustomCursorCallback() = default;
	void perform(const Event &event);
 private:
	Engine* mEngine;
};

} /* flf */
} /* flw */
