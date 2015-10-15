/*
 * Event.h
 *
 *  Created on: 12 May 2014
 *      Author: Filip Wasil
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <fillwave/actions/EventType.h>

namespace fillwave {
namespace actions {

/*! \class Event
 * \brief Template for all events.
 * This class needs to be specialized by the certain type
 * of event You want to be carried.
 */

template<class T>
class Event: public EventType {
public:
	Event(T data)
			: EventType(data.type), mData(data) {

	}
	virtual ~Event() = default;

	static T getData(EventType* eventType) {
		Event<T>* e = dynamic_cast<Event<T>*>(eventType);
		return e->mData;
	}

	static Event<T>* getEvent(EventType* eventType) {
		Event<T>* e = dynamic_cast<Event<T>*>(eventType);
		return e;
	}

private:
	T mData;
};

} /* fillwave */
} /* actions */

#endif /* EVENT_H_ */
