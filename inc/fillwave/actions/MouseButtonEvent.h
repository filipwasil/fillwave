/*
 * MouseButtonEvent.h
 *
 *  Created on: 15 March 2014
 *      Author: Filip Wasil
 */

#ifndef MOUSEBUTTONEVENT_H_
#define MOUSEBUTTONEVENT_H_

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

/*! \struct MouseButtonEventData
 *
 * \brief Event data structure to store the parameters of a button press event.
 *
 */

struct MouseButtonEventData {
	float mWhereX, mWhereY;
	int mButton;
	int mAction;
	int mMods;
	const eEventType type = eEventType::mouseButton;
};

/*! \class MouseButtonEvent
 *
 * \brief Event introduced when something happens with the mouse buttons.
 *
 */

class MouseButtonEvent: public Event<MouseButtonEventData> {
public:
	MouseButtonEvent(MouseButtonEventData data);
	virtual ~MouseButtonEvent();
};

} /* actions */
} /* fillwave */

#endif /* MOUSEBUTTONEVENT_H_ */
