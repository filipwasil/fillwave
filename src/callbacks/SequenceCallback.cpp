/*
 * SequenceCallback.cpp
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/callbacks/SequenceCallback.h>

namespace fillwave {
namespace framework {

SequenceCallback::SequenceCallback() :
	Callback([ & ](EventType & event) {
	if (mReloaditerator) { //xxx refactor ?
		mCallbackIterator = this->begin();
		mReloaditerator = false;
	}

	(*mCallbackIterator).perform(event);
	if ((*mCallbackIterator).getFinished()) {
		mCallbackIterator++;
	}
	if (mCallbackIterator == end()) {
		setFinished(true);
		mCallbackIterator = this->begin();
		for (auto& it : *this) {
			it.setFinished(false);
		}
	}
}, eEventType::eTime),
mCallbackIterator(this->begin()),
mReloaditerator(true) {
}

} /* framework */
} /* fillwave */
