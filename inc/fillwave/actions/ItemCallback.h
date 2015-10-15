/*
 * ItemCallback.h
 *
 *  Created on: 8 May 2014
 *      Author: Filip Wasil
 */

#ifndef ITEMCALLBACK_H_
#define ITEMCALLBACK_H_

#include <fillwave/common/Finishable.h>
#include <fillwave/actions/Event.h>
#include <fillwave/actions/Callback.h>

namespace fillwave {
namespace actions {

/*! \class ItemCallback
 * \brief Base for item callbacks.
 */

class ItemCallback: public common::Finishable, public Callback {
public:
	ItemCallback(eEventType eventType, float timeToFinish = FILLWAVE_ENDLESS)
			: Finishable(timeToFinish), Callback(eventType), mEnabled(true) {
	}

	virtual void perform(EventType* event) = 0;

	~ItemCallback() = default;

	bool isEnabled() {
		return mEnabled;
	}

	void enable() {
		mEnabled = true;
	}

	void disable() {
		mEnabled = false;
	}

protected:
	bool mEnabled;
};

} /* actions */
} /* fillwave */

#endif /* ITEMCALLBACK_H_ */
