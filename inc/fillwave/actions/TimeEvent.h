/*
 * TimeEvent.h
 *
 *  Created on: 13 March 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#ifndef TIMEEVENT_H_
#define TIMEEVENT_H_

#include <fillwave/actions/Event.h>

namespace fillwave {
namespace actions {

/*! \struct TimeEventData
 *
 * \brief Event data structure to store the amount of time expired.
 *
 */

struct TimeEventData {
	float mTimePassed;
	const eEventType type = eEventType::time;
};

/*! \class TimeEvent
 *
 * \brief Event introduced with every single draw loop passed.
 *
 */

class TimeEvent: public Event<TimeEventData> {
public:
	TimeEvent(TimeEventData data);
	virtual ~TimeEvent();
};

} /* actions */
} /* fillwave */

#endif /* TIMEEVENT_H_ */
