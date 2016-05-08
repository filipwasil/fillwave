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
#include <fillwave/common/ExceptionFillwave.h>

#include <memory>
#include <algorithm>

namespace fillwave {
class Engine;
namespace framework {

typedef unsigned long CallbackId;

/*! \class Callback
* \brief Base for all callbacks.
*/
struct Callback: public Finishable {
 public:
	Callback(std::function <void(EventType&)> foo,
	         eEventType eventType, float timeToFinish = FILLWAVE_ENDLESS) :
		mFunction(foo), Finishable(timeToFinish), mEnabled(true),
		mEventType(eventType),
		mId(generateId()) {
	}

	void perform(EventType& event) {
		mFunction(event);
	};

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

	eEventType getEventType() const {
		return mEventType;
	}

	CallbackId getId() const {
		return mId;
	}

	template <class T>
	static void handleEvent(
	   std::vector<T>& callbacks, EventType& event) {
		/* Run callbacks */
		for (auto& it : callbacks) {
			if (it.isEnabled()) {
				if (it.getEventType() == event.getType()) {
					it.perform(event);
				}
			}
		}

		/* Erase finished callbacks */
		auto _find_finished_function =
		   [](T & m) -> bool {return m.getFinished();};
		auto it = std::remove_if(callbacks.begin(), callbacks.end(),
		                         _find_finished_function);
		callbacks.erase(it, callbacks.end());
	}

	static void handleEvent(Engine* engine,
	                        std::vector<CallbackId>& callbackIds, EventType& event);

 protected:
	bool mEnabled;
	eEventType mEventType;
	CallbackId mId;
	std::function<void(EventType&)> mFunction;

 private:
	CallbackId generateId() {
		static CallbackId id = 0;
		return id++;
	};

};

} /* framework */
} /* fillwave */

#endif /* ITEMCALLBACK_H_ */
