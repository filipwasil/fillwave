/*
 * LoopCallback.cpp
 *
 *  Created on: 12 May 2014
 *      Author: filip
 */

#include <fillwave/actions/LoopCallback.h>

namespace fillwave {
namespace actions {

LoopCallback::LoopCallback(Callback* callback, int numberOfExecutions)
		:
				Callback(eEventType::eTime),
				mCallback(callback),
				mLoopsLeft(numberOfExecutions) {
}

void LoopCallback::perform(EventType& event) {
	mCallback->perform(event);
	if (mLoopsLeft != ENDLESS_LOOP) {
		if (mCallback->isFinished()) {
			if (--mLoopsLeft) {
				mCallback->reset();
			} else {
				finish();
			}
		}
	};
}

} /* actions */
} /* fillwave */
