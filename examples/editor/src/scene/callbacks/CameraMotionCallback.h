#pragma once

#include <fillwave/Framework.h>

namespace flw {
class Engine;
namespace flf {

class CameraMotionCallback: public Callback {
 public:
	CameraMotionCallback(Engine* engine);
	virtual ~CameraMotionCallback() = default;
	void perform (EventType& event);
	glm::vec3 calculateNewPosition(float time);
 private:
	float mTimePassed;
	Engine* mEngine;
};

} /* flf */
} /* flw */
