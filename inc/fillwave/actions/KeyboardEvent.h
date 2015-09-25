/*
 * KeyboardEvent.h
 *
 *  Created on: 13 May 2014
 *      Author: Filip Wasil
 */

#ifndef KEYBOARDEVENT_H_
#define KEYBOARDEVENT_H_

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

/*! \struct KeyboardEventData
 *
 * \brief Event data structure to store the parameters of a key event.
 *
 */

struct KeyboardEventData {
   int key,
       scanCode,
       action,
       mode;
   const eEventType type = eEventType::key;
};

/*! \struct KeyboardEvent
 *
 * \brief Event introduced when something happens with the key.
 *
 */

class KeyboardEvent: public Event<KeyboardEventData> {
public:
   KeyboardEvent(KeyboardEventData data);
   virtual ~KeyboardEvent();
};

} /* actions */
} /* fillwave */

#endif /* KEYBOARDEVENT_H_ */
