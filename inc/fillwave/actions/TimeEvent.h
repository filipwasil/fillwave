/*
 * TimeEvent.h
 *
 *  Created on: 13 March 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEEVENT_H_
#define TIMEEVENT_H_

#include <fillwave/actions/Event.h>

namespace fillwave {
namespace actions {

/*! \struct TimeEventData
 * \brief Event data structure to store the amount of time expired.
 */

struct TimeEventData {
	float mTimePassed;
	const eEventType type = eEventType::time;
};

/*! \class TimeEvent
 * \brief Event introduced with every single draw loop passed.
 */

class TimeEvent: public Event<TimeEventData> {
public:
	TimeEvent(TimeEventData data)
			: Event(data) {

	}
	virtual ~TimeEvent() = default;
};

} /* actions */
} /* fillwave */

#endif /* TIMEEVENT_H_ */
