/*
 * TimedScaleCallback.cpp
 *
 *  Created on: 15 May 2014
 *      Author: Filip Wasil
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
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/actions/TimedScaleCallback.h>
#include <fillwave/actions/TimeEvent.h>

namespace fillwave {
namespace actions {

TimedScaleCallback::TimedScaleCallback(pEntity entity,
                                       glm::vec3 normalizedScaleVec,
                                       GLfloat lifetime,
                                       eEasing easing)
:TimedCallback(lifetime, easing),
 mEndScale(normalizedScaleVec),
 mEntity(entity){

}

TimedScaleCallback::TimedScaleCallback(pEntity entity,
      GLfloat normalizedScale,
      GLfloat lifetime,
      eEasing easing)
:TimedCallback(lifetime, easing),
 mEndScale(normalizedScale,
           normalizedScale,
           normalizedScale),
 mEntity(entity) {

}

TimedScaleCallback::~TimedScaleCallback() {

}

void TimedScaleCallback::performTime(TimeEventData& data) {
   if (getPercentageDone() == 0.0) {
      mStartScale = mEntity->getScale();
   }
   mTimePassed += data.mTimePassed;
   mEntity->scaleTo(mStartScale + ease(getPercentageDone()) * ( mEndScale - mStartScale ) );
}

} /* actions */
} /* fillwave */
