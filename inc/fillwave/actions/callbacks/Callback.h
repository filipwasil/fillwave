/*
 * Callback.h
 *
 *  Created on: 8 May 2014
 *      Author: Filip Wasil
 */

#ifndef  CALLBACK_H_
#define  CALLBACK_H_

#include <fillwave/common/Finishable.h>
#include <fillwave/actions/events/TEvent.h>
#include <memory>
#include <algorithm>

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

	template <class T>
	static void handleEvent(
	   std::vector<T>& callbacks, EventType& event) {
		/* Run callbacks */
		for (auto& it : callbacks) {
			if (it->isEnabled()) {
				if (it->getEventType() == event.getType()) {
					it->perform(event);
				}
			}
		}

		/* Erase finished callbacks */
		auto _find_finished_function =
		   [](T & m) -> bool {return m->isFinished();};
		auto _begin = callbacks.begin();
		auto _end = callbacks.end();
		auto it = std::remove_if(_begin, _end, _find_finished_function);
		callbacks.erase(it, _end);
	}

 protected:
	bool mEnabled;
	eEventType mEventType;
};

} /* framework */
typedef std::unique_ptr<framework::Callback> puCallback;
} /* fillwave */

#endif /* ITEMCALLBACK_H_ */
