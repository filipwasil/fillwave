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
		: EngineCallback(eEventType::time), mTimePassed(0.0), mText(text) {

}

FPSCallback::~FPSCallback() {

}

void FPSCallback::perform(Engine* engine, EventType* event) { //xxx make this more generic
	TimeEventData e = TimeEvent::getData(event);
	if (mTimePassed < 1.0) {
		mTimePassed += e.mTimePassed;
	} else {
		mTimePassed -= 1.0;
		mText->editString(
				std::string("FPS ")
						+ strings::to_string<GLuint>(engine->getFramesPassed()));
	}
}

} /* actions */
} /* fillwave */
