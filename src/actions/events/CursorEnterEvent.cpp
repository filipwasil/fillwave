/*
 * CursorEnterEvent.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: filip
 */

#include <fillwave/actions/CursorEnterEvent.h>

namespace fillwave {
namespace actions {

CursorEnterEvent::CursorEnterEvent(CursorEnterEventData& data)
		: Event<CursorEnterEventData>(data) {

}

CursorEnterEvent::~CursorEnterEvent() {

}

} /* actions */
} /* fillwave */
