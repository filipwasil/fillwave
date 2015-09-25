/*
 * CursorEnterEvent.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Filip Wasil
 */

#ifndef CURSORENTEREVENT_H_
#define CURSORENTEREVENT_H_

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

/*! \struct CursorEnterEventData
 *
 * \brief Event data structure to store the CursorEntered/CursorLeaved data.
 *
 */

struct CursorEnterEventData {
	int direction;
	const eEventType type = eEventType::cursorEnter;
};

/*! \struct CursorEnterEvent
 *
 * \brief Event introduced when cursor enters the window.
 *
 */

class CursorEnterEvent: public Event<CursorEnterEventData> {
public:
	CursorEnterEvent(CursorEnterEventData& data);
	virtual ~CursorEnterEvent();
};

} /* actions */
} /* fillwave */

#endif /* CURSORENTEREVENT_H_ */
