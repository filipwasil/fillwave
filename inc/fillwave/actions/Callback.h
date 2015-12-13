/*
 * Callback.h
 *
 *  Created on: 8 May 2014
 *      Author: Filip Wasil
 */

#ifndef  CALLBACK_H_
#define  CALLBACK_H_

#include <fillwave/common/Finishable.h>
#include <fillwave/actions/Event.h>
#include <fillwave/actions/Callback.h>
#include <memory>

namespace fillwave {
namespace actions {

/*! \class ItemCallback
 * \brief Base for item callbacks.
 */

class Callback: public common::Finishable {
public:
	Callback(eEventType eventType, float timeToFinish = FILLWAVE_ENDLESS)
			: Finishable(timeToFinish), mEnabled(true), mEventType(eventType) {
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

} /* actions */
typedef std::unique_ptr<actions::Callback> puCallback;
} /* fillwave */

#endif /* ITEMCALLBACK_H_ */
