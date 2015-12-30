/*
 * TouchEvent.h
 *
 *  Created on: Jan 11, 2015
 *      Author: filip
 */

#ifndef TOUCHEVENT_H_
#define TOUCHEVENT_H_

#include <fillwave/actions/events/Event.h>

namespace fillwave {
namespace framework {

/*! \struct TouchEventData
 * \brief Event data structure to store the character together with modifier keys.
 */

struct TouchEventData {
	int xPos;
	int yPos;
	int action;
	const eEventType type = eEventType::eTouch;
};

/*! \struct TouchEvent
 * \brief Event introduced when the screen is pressed.
 */

class TouchEvent: public Event<TouchEventData> {
public:
	TouchEvent(TouchEventData& data)
			: Event<TouchEventData>(data) {

	}
	virtual ~TouchEvent() = default;
};

} /* framework */
} /* fillwave */

#endif /* TOUCHEVENT_H_ */
