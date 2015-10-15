/*
 * SequenceCallback.cpp
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/SequenceCallback.h>
#include <fillwave/actions/ItemCallback.h>

namespace fillwave {
namespace actions {

SequenceCallback::SequenceCallback()
		:
				ItemCallback(eEventType::time),
				mCallbackIterator(this->begin()),
				mReloaditerator(true) {
}

SequenceCallback::~SequenceCallback() {
	for (auto it : *this) {
		delete it;
	}
}

void SequenceCallback::perform(EventType* event) {
	if (mReloaditerator) {
		mCallbackIterator = this->begin();
		mReloaditerator = false;
	}

	(*mCallbackIterator)->perform(event);
	if ((*mCallbackIterator)->isFinished()) {
		mCallbackIterator++;
	}
	if (mCallbackIterator == end()) {
		finish();
		mCallbackIterator = this->begin();
		for (auto it : *this) {
			it->reset();
		}
	}
}

} /* actions */
} /* fillwave */
