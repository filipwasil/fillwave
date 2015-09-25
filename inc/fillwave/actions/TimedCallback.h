/*
 * TimedCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDCALLBACK_H_
#define TIMEDCALLBACK_H_

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

#include <fillwave/common/Finishable.h>
#include <fillwave/actions/ItemCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/actions/Callback.h>
#include <fillwave/models/Entity.h>

namespace fillwave {

enum class eEasing {
   None,

   SineIn,
   SineOut,
   SineInOut,

   QuadIn,
   QuadOut,
   QuadInOut,

   CubicIn,
   CubicOut,
   CubicInOut,

   QuartIn,
   QuartOut,
   QuartInOut,

   QuintIn,
   QuintOut,
   QuintInOut,

   ExpoIn,
   ExpoOut,
   ExpoInOut,

   CircIn,
   CircOut,
   CircInOut,

   BackIn,
   BackOut,
   BackInOut,

   ElasticIn,
   Elastic,
   ElasticInOut,

   BounceIn,
   Bounce,
   BounceInOut,

   Custom
};

namespace actions {

/*! \class TimedCallback
 *
 * \brief ItemCallback to be finished after a period of time.
 *
 */

class TimedCallback: public ItemCallback {
public:
   TimedCallback(GLfloat timeToFinish,
                 eEasing easing = eEasing::None);
   virtual ~TimedCallback();

   /*
    * perform
    *
    * \brief Performs ItemCallback action.
    */

   void perform(EventType* eventType);

   virtual void performTime(TimeEventData& e);

   virtual GLfloat easeCustom(GLfloat progress);

   GLfloat ease(GLfloat progress);

private:
   eEasing mEasing;
};

} /* actions */
} /* fillwave */

#endif /* TIMEDCALLBACK_H_ */

