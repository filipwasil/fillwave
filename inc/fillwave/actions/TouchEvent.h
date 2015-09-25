/*
 * TouchEvent.h
 *
 *  Created on: Jan 11, 2015
 *      Author: filip
 */

#ifndef TOUCHEVENT_H_
#define TOUCHEVENT_H_

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

/*! \struct TouchEventData
 * \brief Event data structure to store the character together with modifier keys.
 */

struct TouchEventData {
   int xPos;
   int yPos;
   int action;
   const eEventType type = eEventType::touch;
};

/*! \struct TouchEvent
 * \brief Event introduced when the screen is pressed.
 */

class TouchEvent: public Event<TouchEventData> {
public:
   TouchEvent(TouchEventData& data);
   virtual ~TouchEvent();
   };

} /* actions */
} /* fillwave */

#endif /* TOUCHEVENT_H_ */
