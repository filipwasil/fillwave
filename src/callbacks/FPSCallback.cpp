/*
 * TextRefresheCallback.cpp
 *
 *  Created on: Nov 1, 2014
 *      Author: filip
 */

#include <fillwave/actions/callbacks/FPSCallback.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>

FLOGINIT("FPSCallback", FERROR | FFATAL)

namespace fillwave {
namespace framework {

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
						+ to_string<GLuint>(mEngine->getFramesPassed()));
	}
}

} /* framework */
} /* fillwave */
