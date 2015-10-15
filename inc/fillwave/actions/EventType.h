/*
 * EventType.h
 *
 *  Created on: Oct 1, 2014
 *      Author: Filip Wasil
 */

#ifndef EVENTTYPE_H_
#define EVENTTYPE_H_

namespace fillwave {

enum class eEventType {
	mouseButton,
	cursorPosition,
	cursorEnter,
	scroll,
	key,
	character,
	characterMods,
	time,
	touch,
	custom0,
	custom1,
	custom2,
	custom3,
	custom4,
	custom5,
	custom6,
	custom7,
	custom8,
	custom9,
	custom10,
	custom11,
	custom12,
	custom13,
	custom14,
	custom15
};

namespace actions {

/*! \class EventType
 * \brief Base class for all events.
 * This class needs only the event type (literally - an enumerator)
 * to initialize. Event type defines by which callback the event will be handled.
 */

class EventType {
public:
	EventType(eEventType type)
			: mType(type) {
	}
	virtual ~EventType() = default;

	eEventType getType() {
		return mType;
	}

private:
	eEventType mType;
};

} /* actions */
} /* fillwave */

#endif /* EVENTTYPE_H_ */
