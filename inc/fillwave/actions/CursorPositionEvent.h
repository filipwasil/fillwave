/*
 * CursorPositionEvent.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Filip Wasil
 */

#ifndef CURSORPOSITIONEVENT_H_
#define CURSORPOSITIONEVENT_H_

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

#include <fillwave/actions/Event.h>

namespace fillwave {
namespace actions {

/*! \struct CursorPositionEventData
 *
 * \brief Event data structure to store the cursor position.
 *
 */

struct CursorPositionEventData {
	double xPosition;
	double yPosition;
	const eEventType type = eEventType::cursorPosition;
};

/*! \struct CursorPositionEvent
 *
 * \brief Event introduced when cursor position was changed.
 *
 */

class CursorPositionEvent: public Event<CursorPositionEventData> {
public:
	CursorPositionEvent(CursorPositionEventData& data);
	virtual ~CursorPositionEvent();
};

} /* actions */
} /* fillwave */

#endif /* CURSORPOSITIONEVENT_H_ */
