/*
 * Event.h
 *
 *  Created on: 12 May 2014
 *      Author: Filip Wasil
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <fillwave/actions/events/EventType.h>

namespace fillwave {
namespace framework {

/*! \class Event
 * \brief Template for all events.
 * This class needs to be specialized by the certain type
 * of event You want to be carried.
 */

template<class T>
class TEvent: public EventType {
public:
	TEvent(T data)
			: EventType(data.type), mData(data) {

	}
	virtual ~TEvent() = default;

	static T getData(EventType& eventType) {
		TEvent<T>* e = static_cast<TEvent<T>*>(&eventType);
		return e->mData;
	}

	static TEvent<T>* getEvent(EventType* eventType) {
		TEvent<T>* e = static_cast<TEvent<T>*>(eventType);
		return e;
	}

private:
	T mData;
};

} /* framework */
} /* fillwave */

#endif /* EVENT_H_ */
