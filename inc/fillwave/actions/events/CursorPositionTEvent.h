/*
 * CursorPositionEvent.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Filip Wasil
 */

#ifndef CURSORPOSITIONEVENT_H_
#define CURSORPOSITIONEVENT_H_

#include <fillwave/actions/events/TEvent.h>

namespace flw {
namespace flf {

/*! \struct CursorPositionEventData
 * \brief Event data structure to store the cursor position.
 */

struct CursorPositionEventData {
  double xPosition;
  double yPosition;
  const eEventType type = eEventType::eCursorPosition;
};

/*! \struct CursorPositionEvent
 * \brief Event introduced when cursor position was changed.
 */

class CursorPositionEvent : public TEvent<CursorPositionEventData> {
public:
  CursorPositionEvent(CursorPositionEventData &data)
      : TEvent<CursorPositionEventData>(data) {

  }

  virtual ~CursorPositionEvent() = default;
};

} /* flf */
} /* flw */

#endif /* CURSORPOSITIONEVENT_H_ */
