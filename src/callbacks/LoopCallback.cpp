/*
 * LoopCallback.cpp
 *
 *  Created on: 12 May 2014
 *      Author: filip
 */

#include <fillwave/actions/callbacks/LoopCallback.h>

namespace fillwave {
namespace framework {

LoopCallback::LoopCallback(puCallback&& callback, int numberOfExecutions) :
	Callback(eEventType::eTime),
	mCallback(std::move(callback)),
	mLoopsLeft(numberOfExecutions) {
}

void LoopCallback::perform(EventType& event) {
	mCallback->perform(event);
	if (mLoopsLeft != FILLWAVE_ENDLESS) {
		if (mCallback->isFinished()) {
			if (--mLoopsLeft) {
				mCallback->reset();
			} else {
				finish();
			}
		}
	};
}

} /* framework */
} /* fillwave */
