/*
 * CursorEnterEvent.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Filip Wasil
 */

#ifndef CURSORENTEREVENT_H_
#define CURSORENTEREVENT_H_

#include <fillwave/actions/events/TEvent.h>

namespace fillwave {
namespace framework {

/*! \struct CursorEnterEventData
 * \brief Event data structure to store the CursorEntered/CursorLeaved data.
 */

struct CursorEnterEventData {
	int direction;
	const eEventType type = eEventType::eCursorEnter;
};

/*! \struct CursorEnterEvent
 * \brief Event introduced when cursor enters the window.
 */

class CursorEnterEvent: public TEvent<CursorEnterEventData> {
public:
	CursorEnterEvent(CursorEnterEventData& data) :
			TEvent(data) {

	}

	virtual ~CursorEnterEvent() = default;
};

} /* framework */
} /* fillwave */

#endif /* CURSORENTEREVENT_H_ */
