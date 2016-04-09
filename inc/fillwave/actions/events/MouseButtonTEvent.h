/*
 * MouseButtonEvent.h
 *
 *  Created on: 15 March 2014
 *      Author: Filip Wasil
 */

#ifndef MOUSEBUTTONEVENT_H_
#define MOUSEBUTTONEVENT_H_

#include <fillwave/actions/events/TEvent.h>

namespace fillwave {
namespace framework {

/*! \struct MouseButtonEventData
 * \brief Event data structure to store the parameters of a button press event.
 */

struct MouseButtonEventData {
	float mWhereX, mWhereY;
	int mButton;
	int mAction;
	int mMods;
	const eEventType type = eEventType::eMouseButton;
};

/*! \class MouseButtonEvent
 * \brief Event introduced when something happens with the mouse buttons.
 */

class MouseButtonEvent: public TEvent<MouseButtonEventData> {
 public:
	MouseButtonEvent(MouseButtonEventData data) :
		TEvent(data) {

	}
	virtual ~MouseButtonEvent() = default;
};

} /* framework */
} /* fillwave */

#endif /* MOUSEBUTTONEVENT_H_ */
