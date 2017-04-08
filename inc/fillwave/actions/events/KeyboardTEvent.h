/*
 * KeyboardEvent.h
 *
 *  Created on: 13 May 2014
 *      Author: Filip Wasil
 */

#ifndef KEYBOARDEVENT_H_
#define KEYBOARDEVENT_H_

#include <fillwave/actions/events/TEvent.h>

namespace flw {
namespace flf {

/*! \struct KeyboardEventData
 * \brief Event data structure to store the parameters of a key event.
 */

struct KeyboardEventData {
  int key, scanCode, action, mode;
  const eEventType type = eEventType::eKey;
};

/*! \struct KeyboardEvent
 * \brief Event introduced when something happens with the key.
 */

class KeyboardEvent : public TEvent<KeyboardEventData> {
public:
  KeyboardEvent(KeyboardEventData data)
      : TEvent(data) {

  }

  virtual ~KeyboardEvent() = default;
};

} /* flf */
} /* flw */

#endif /* KEYBOARDEVENT_H_ */
