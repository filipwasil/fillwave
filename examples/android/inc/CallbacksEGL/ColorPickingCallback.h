/*
 * ColorPickingCallback.h
 *
 *  Created on: Jan 16, 2015
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

#ifndef COLORPICKINGCALLBACKMODEL_H_
#define COLORPICKINGCALLBACKMODEL_H_

#include "../../../android/inc/CallbacksEGL/ColorPickingCallback.h"

#include <fillwave/Fillwave.h>
#include <fillwave/actions/callbacks/Callback.h>

namespace flw {
namespace flf {

class ColorPickingCallback : public Callback {
public:
  ColorPickingCallback(Engine *engine);

  ~ColorPickingCallback() = default;

  void perform(EventType &event);
};

} /* framework */
} /* fillwave */

#endif /* COLORPICKINGCALLBACKMODEL_H_ */
