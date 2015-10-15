/*
 * CursorPositionEvent.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Filip Wasil
 */

#ifndef CURSORPOSITIONEVENT_H_
#define CURSORPOSITIONEVENT_H_

#include <fillwave/actions/Event.h>

namespace fillwave {
namespace actions {

/*! \struct CursorPositionEventData
 * \brief Event data structure to store the cursor position.
 */

struct CursorPositionEventData {
	double xPosition;
	double yPosition;
	const eEventType type = eEventType::cursorPosition;
};

/*! \struct CursorPositionEvent
 * \brief Event introduced when cursor position was changed.
 */

class CursorPositionEvent: public Event<CursorPositionEventData> {
public:
	CursorPositionEvent(CursorPositionEventData& data)
			: Event<CursorPositionEventData>(data) {

	}
	virtual ~CursorPositionEvent() = default;
};

} /* actions */
} /* fillwave */

#endif /* CURSORPOSITIONEVENT_H_ */
