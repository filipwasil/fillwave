/*
 * TextRefresheCallback.cpp
 *
 *  Created on: Nov 1, 2014
 *      Author: filip
 */

#include <fillwave/actions/FPSCallback.h>
#include <fillwave/Fillwave.h>
#include <fillwave/extras/Log.h>

FLOGINIT("FPSCallback", FERROR | FFATAL)

namespace fillwave {
namespace actions {

FPSCallback::FPSCallback(pText text)
		: EngineCallback(eEventType::time), mText(text), mTimePassed(0.0) {

}

void FPSCallback::perform(Engine* engine, EventType* event) {
	TimeEventData e = TimeEvent::getData(event);
	if (mTimePassed < 1.0f) {
		mTimePassed += e.mTimePassed;
	} else {
		mTimePassed -= 1.0f;
		mText->editString(
				std::string("FPS ")
						+ strings::to_string<GLuint>(engine->getFramesPassed()));
	}
}

} /* actions */
} /* fillwave */
