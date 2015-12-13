/*
 * ColorPickingCallback.h
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

#ifndef COLORPICKINGCALLBACK_H_
#define COLORPICKINGCALLBACK_H_

#include <fillwave/actions/Callback.h>
#include <fillwave/models/Entity.h>
#include <fillwave/actions/Event.h>

namespace fillwave {
class Engine;
namespace actions {

/*! \class ColorPickingCallback
 *
 * \brief EngineCallback to handle pickable elements.
 *
 */

class ColorPickingCallback: public Callback {
public:
   ColorPickingCallback(Engine* engine);
   virtual ~ColorPickingCallback() = default;
   void perform (EventType& eventType);
private:
   pEntity mCurrentlyPicked;
	Engine* mEngine;
};

} /* actions */
} /* fillwave */

#endif /* COLORPICKINGCALLBACK_H_ */
