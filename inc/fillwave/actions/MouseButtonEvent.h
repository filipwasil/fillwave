/*
 * MouseButtonEvent.h
 *
 *  Created on: 15 March 2014
 *      Author: Filip Wasil
 */

#ifndef MOUSEBUTTONEVENT_H_
#define MOUSEBUTTONEVENT_H_

#include <fillwave/actions/Event.h>

namespace fillwave {
namespace actions {

/*! \struct MouseButtonEventData
 * \brief Event data structure to store the parameters of a button press event.
 */

struct MouseButtonEventData {
	float mWhereX, mWhereY;
	int mButton;
	int mAction;
	int mMods;
	const eEventType type = eEventType::mouseButton;
};

/*! \class MouseButtonEvent
 * \brief Event introduced when something happens with the mouse buttons.
 */

class MouseButtonEvent: public Event<MouseButtonEventData> {
public:
	MouseButtonEvent(MouseButtonEventData data)
			: Event(data) {

	}
	virtual ~MouseButtonEvent() = default;
};

} /* actions */
} /* fillwave */

#endif /* MOUSEBUTTONEVENT_H_ */
