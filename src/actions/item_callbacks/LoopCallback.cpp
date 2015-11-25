/*
 * LoopCallback.cpp
 *
 *  Created on: 12 May 2014
 *      Author: filip
 */

#include <fillwave/actions/LoopCallback.h>

namespace fillwave {
namespace actions {

LoopCallback::LoopCallback(ItemCallback* callback, int numberOfExecutions)
		:
				ItemCallback(eEventType::eTime),
				mItemCallback(callback),
				mLoopsLeft(numberOfExecutions) {
}

void LoopCallback::perform(EventType* event) {
	mItemCallback->perform(event);
	if (mLoopsLeft != ENDLESS_LOOP) {
		if (mItemCallback->isFinished()) {
			if (--mLoopsLeft) {
				mItemCallback->reset();
			} else {
				finish();
			}
		}
	};
}

} /* actions */
} /* fillwave */
