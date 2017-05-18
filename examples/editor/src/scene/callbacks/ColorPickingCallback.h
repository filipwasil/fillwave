#pragma once

#include <fillwave/Framework.h>

namespace flw {
class Engine;
namespace flf {

class ColorPickingCallback: public Callback {
 public:
	ColorPickingCallback(Engine* engine);
	virtual ~ColorPickingCallback() = default;
	void perform (EventType& eventType);
 private:
	Entity* mCurrentlyPicked;
	Engine* mEngine;
};

} /* flf */
} /* flw */
