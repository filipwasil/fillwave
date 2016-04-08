/*
 * Callback.h
 *
 *  Created on: 8 May 2014
 *      Author: Filip Wasil
 */

#ifndef  CALLBACK_H_
#define  CALLBACK_H_

#include <fillwave/common/Finishable.h>
#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/events/TEvent.h>
#include <memory>

namespace fillwave {
namespace framework {

/*! \class Callback
 * \brief Base for all callbacks.
 */

class Callback: public Finishable {
public:
	Callback(eEventType eventType, float timeToFinish = FILLWAVE_ENDLESS) :
			Finishable(timeToFinish), mEnabled(true), mEventType(eventType) {
	}

	virtual void perform(EventType& event) = 0;

	~Callback() = default;

	bool isEnabled() {
		return mEnabled;
	}

	void enable() {
		mEnabled = true;
	}

	void disable() {
		mEnabled = false;
	}

	eEventType getEventType() {
		return mEventType;
	}

protected:
	bool mEnabled;
	eEventType mEventType;
};

} /* framework */
typedef std::unique_ptr<framework::Callback> puCallback;
} /* fillwave */

#endif /* ITEMCALLBACK_H_ */
