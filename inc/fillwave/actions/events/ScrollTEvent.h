/*
 * ScrollEvent.h
 *
 *  Created on: Oct 1, 2014
 *      Author: Filip Wasil
 */

#ifndef SCROLLEVENT_H_
#define SCROLLEVENT_H_

#include <fillwave/actions/events/TEvent.h>

namespace fillwave {
namespace framework {

/*! \struct ScrollEventData
 * \brief Event data structure to store the parameters of scrolling action.
 */

struct ScrollEventData {
	double mOffsetX, mOffsetY;
	const eEventType type = eEventType::eScroll;
};

/*! \struct ScrollEvent
 * \brief Event introduced together with scrolling action.
 */

class ScrollEvent: public TEvent<ScrollEventData> {
 public:
	ScrollEvent(ScrollEventData data) :
		TEvent(data) {

	}
	virtual ~ScrollEvent() = default;
};

} /* framework */
} /* fillwave */

#endif /* SCROLLEVENT_H_ */
