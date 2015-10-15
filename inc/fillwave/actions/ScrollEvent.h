/*
 * ScrollEvent.h
 *
 *  Created on: Oct 1, 2014
 *      Author: Filip Wasil
 */

#ifndef SCROLLEVENT_H_
#define SCROLLEVENT_H_

#include <fillwave/actions/Event.h>

namespace fillwave {
namespace actions {

/*! \struct ScrollEventData
 * \brief Event data structure to store the parameters of scrolling action.
 */

struct ScrollEventData {
	double mOffsetX, mOffsetY;
	const eEventType type = eEventType::scroll;
};

/*! \struct ScrollEvent
 * \brief Event introduced together with scrolling action.
 */

class ScrollEvent: public Event<ScrollEventData> {
public:
	ScrollEvent(ScrollEventData data)
			: Event(data) {

	}
	virtual ~ScrollEvent() = default;
};

} /* actions */
} /* fillwave */

#endif /* SCROLLEVENT_H_ */
