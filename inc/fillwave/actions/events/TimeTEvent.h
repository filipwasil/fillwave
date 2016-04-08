/*
 * TimeEvent.h
 *
 *  Created on: 13 March 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEEVENT_H_
#define TIMEEVENT_H_

#include <fillwave/actions/events/TEvent.h>

namespace fillwave {
namespace framework {

/*! \struct TimeEventData
 * \brief Event data structure to store the amount of time expired.
 */

struct TimeEventData {
	float mTimePassed;
	const eEventType type = eEventType::eTime;
};

/*! \class TimeEvent
 * \brief Event introduced with every single draw loop passed.
 */

class TimeEvent: public TEvent<TimeEventData> {
  public:
	TimeEvent(TimeEventData data) :
		TEvent(data) {

	}
	virtual ~TimeEvent() = default;
};

} /* framework */
} /* fillwave */

#endif /* TIMEEVENT_H_ */
