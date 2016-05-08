/*
 * LoopCallback.cpp
 *
 *  Created on: 12 May 2014
 *      Author: filip
 */

#include <fillwave/actions/callbacks/LoopCallback.h>

namespace fillwave {
namespace framework {

void doopa(EventType&) {
	;
}
LoopCallback::LoopCallback(const Callback&& callback, int numberOfExecutions) :
	Callback([ & ](EventType & event) {
	mCallback.perform(event);
	if (mLoopsLeft != FILLWAVE_ENDLESS) {
		if (mCallback.getFinished()) {
			if (--mLoopsLeft) {
				mCallback.setFinished(false);
			} else {
				mCallback.setFinished(true);
			}
		}
	};
}, eEventType::eTime),
mCallback(callback),
mLoopsLeft(numberOfExecutions) {
}

} /* framework */
} /* fillwave */
