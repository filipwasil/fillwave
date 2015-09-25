/*
 * EventType.h
 *
 *  Created on: Oct 1, 2014
 *      Author: Filip Wasil
 */

#ifndef EVENTTYPE_H_
#define EVENTTYPE_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

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
 *
 * \brief Base class for all events.
 *
 * This class needs only the event type (literally - an enumerator)
 * to initialize. Event type defines by which callback the event will be handled.
 *
 */

class EventType {
public:
	EventType(eEventType type);
	virtual ~EventType();
	eEventType getType() {
		return mType;
	}
private:
	eEventType mType;
};

} /* actions */
} /* fillwave */

#endif /* EVENTTYPE_H_ */
