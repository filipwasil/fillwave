/*
 * ColorPickingCallback.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
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
 * fillwave@gmail.com
 *
 */

#include "../../../android/inc/CallbacksEGL/ColorPickingCallback.h"

#include <fillwave/Fillwave.h>

FLOGINIT("ColorPickingCallback", FERROR | FFATAL)

namespace fillwave {
namespace framework {

ColorPickingCallback::ColorPickingCallback(Engine *engine)
    : Callback(eEventType::eTouch), mEngine(engine) {

}

void ColorPickingCallback::perform(EventType &event) {
  TouchEventData e = TouchEvent::getData(event);
  mEngine->pick(e.xPos, e.yPos);
}

} /* framework */
} /* fillwave */
