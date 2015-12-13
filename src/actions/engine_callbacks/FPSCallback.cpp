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

FPSCallback::FPSCallback(Engine* engine, pText text)
		:
				Callback(eEventType::eTime),
				mText(text),
				mTimePassed(0.0),
				mEngine(engine) {

}

void FPSCallback::perform(EventType& event) {
	TimeEventData e = TimeEvent::getData(event);
	if (mTimePassed < 1.0f) {
		mTimePassed += e.mTimePassed;
	} else {
		mTimePassed -= 1.0f;
		mText->editString(
				std::string("FPS ")
						+ common::to_string<GLuint>(mEngine->getFramesPassed()));
	}
}

} /* actions */
} /* fillwave */
