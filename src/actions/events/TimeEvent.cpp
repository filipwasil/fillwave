/*
 * TimeEvent.cpp
 *
 *  Created on: 9 May 2014
 *      Author: wasilfil
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

#include <fillwave/actions/TimeEvent.h>

namespace fillwave {
namespace actions {

TimeEvent::TimeEvent(TimeEventData data)
		: Event(data) {

}

TimeEvent::~TimeEvent() {
}

} /* actions */
} /* fillwave */
