/*
 * EngineCallback.h
 *
 *  Created on: Jun 21, 2014
 *      Author: Filip Wasil
 */

#ifndef ENGINECALLBACK_H_
#define ENGINECALLBACK_H_

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

#include <fillwave/actions/Callback.h>

namespace fillwave {
class Engine;
namespace actions {
class EventType;

/*! \class EngineCallback
 *
 * \brief Base for engine-aware callbacks.
 *
 */

class EngineCallback: public Callback {
public:
   EngineCallback(eEventType eventType);
   virtual ~EngineCallback();

   /*
    * perform
    *
    * \brief virtual: Performs EngineCallback action
    */

   virtual void perform (Engine* engine, EventType* eventType) = 0;
};

} /* actions */
} /* fillwave */

#endif /* ENGINECALLBACK_H_ */
