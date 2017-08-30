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

#include "CallbacksGLFW/ColorPickingCallback.h"
//#include <fillwave/Log.h>

#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>

//FLOGINIT("ColorPickingCallback", FERROR | FFATAL)

namespace flw {
namespace flf {

ColorPickingCallback::ColorPickingCallback(Engine *engine)
    : Callback(eEventType::eMouseButton), mEngine(engine) {

}

void ColorPickingCallback::perform(EventType &event) {
  MouseButtonEventData e = MouseButtonEvent::getData(event);
  if (e.mAction == GLFW_RELEASE) {
    mEngine->pick(e.mWhereX, e.mWhereY);
  }
}

} /* framework */
} /* fillwave */
