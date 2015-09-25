/*
 * FPSCallback.h
 *
 *  Created on: Jan 1, 2015
 *      Author: Filip Wasil
 */

#ifndef FPSCALLBACK_H_
#define FPSCALLBACK_H_

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

#include <fillwave/actions/EngineCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/actions/Callback.h>
#include <fillwave/models/Text.h>

namespace fillwave {
class Engine;
namespace actions {

/*! \class FPSCallback
 * \brief ItemCallback to display and refresh FPS as a renderable text.
 *
 */

class FPSCallback: public EngineCallback {
public:
   FPSCallback(pText text);
   virtual ~FPSCallback();
   void perform (Engine* engine, EventType* event);

private:
   pText mText;
   GLfloat mTimePassed;
};

} /* actions */
} /* fillwave */

#endif /* FPSCALLBACK_H_ */
