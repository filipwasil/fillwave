/*
 * CursorPositionEvent.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: filip
 */

#include <fillwave/actions/CursorPositionEvent.h>

namespace fillwave {
namespace actions {

CursorPositionEvent::CursorPositionEvent(CursorPositionEventData& data)
		: Event<CursorPositionEventData>(data) {

}

CursorPositionEvent::~CursorPositionEvent() {

}

} /* actions */
} /* fillwave */
