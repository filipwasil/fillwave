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
	eMouseButton,
	eCursorPosition,
	eCursorEnter,
	eScroll,
	eKey,
	eCharacter,
	eCharacterMods,
	eTime,
	eTouch,
	eResizeScreen,
	eCustom0,
	eCustom1,
	eCustom2,
	eCustom3,
	eCustom4,
	eCustom5,
	eCustom6,
	eCustom7,
	eCustom8,
	eCustom9,
	eCustom10,
	eCustom11,
	eCustom12,
	eCustom13,
	eCustom14,
	eCustom15
};

namespace framework {

/*! \class EventType
 * \brief Base class for all events.
 * This class needs only the event type (literally - an enumerator)
 * to initialize. Event type defines by which callback the event will be handled.
 */

class EventType {
 public:
	EventType(eEventType type) :
		mType(type) {
	}
	virtual ~EventType() = default;

	eEventType getType() {
		return mType;
	}

 private:
	eEventType mType;
};

} /* framework */
} /* fillwave */

#endif /* EVENTTYPE_H_ */
