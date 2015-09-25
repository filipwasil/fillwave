/*
 * ScrollEvent.h
 *
 *  Created on: Oct 1, 2014
 *      Author: Filip Wasil
 */

#ifndef SCROLLEVENT_H_
#define SCROLLEVENT_H_

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

/*! \struct ScrollEventData
 *
 * \brief Event data structure to store the parameters of scrolliing action.
 *
 */

struct ScrollEventData {
	double mOffsetX, mOffsetY;
	const eEventType type = eEventType::scroll;
};

/*! \struct ScrollEvent
 *
 * \brief Event introduced together with scrolling action.
 *
 */

class ScrollEvent: public Event<ScrollEventData> {
public:
	ScrollEvent(ScrollEventData data);
	virtual ~ScrollEvent();
};

} /* actions */
} /* fillwave */

#endif /* SCROLLEVENT_H_ */
