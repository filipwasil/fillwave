/*
 * KeyboardEvent.h
 *
 *  Created on: 13 May 2014
 *      Author: Filip Wasil
 */

#ifndef KEYBOARDEVENT_H_
#define KEYBOARDEVENT_H_

#include <fillwave/actions/Event.h>

namespace fillwave {
namespace actions {

/*! \struct KeyboardEventData
 * \brief Event data structure to store the parameters of a key event.
 */

struct KeyboardEventData {
	int key, scanCode, action, mode;
	const eEventType type = eEventType::eKey;
};

/*! \struct KeyboardEvent
 * \brief Event introduced when something happens with the key.
 */

class KeyboardEvent: public Event<KeyboardEventData> {
public:
	KeyboardEvent(KeyboardEventData data)
			: Event(data) {

	}
	virtual ~KeyboardEvent() = default;
};

} /* actions */
} /* fillwave */

#endif /* KEYBOARDEVENT_H_ */
