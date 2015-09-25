/*
 * TimedMoveCallback.cpp
 *
 *  Created on: 14 May 2014
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

#include <fillwave/actions/TimedMoveCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/extras/Log.h>

namespace fillwave {
namespace actions {

TimedMoveCallback::TimedMoveCallback(pEntity entity,
                                     glm::vec3 endPosition,
                                     GLfloat lifeTime,
                                     eEasing easing)
:TimedCallback(lifeTime, easing),
 mStartPosition (glm::vec3(0.0)), /*to avoid warning*/
 mEndPosition(endPosition),
 mEntity(entity) {

}

TimedMoveCallback::~TimedMoveCallback() {

}

void TimedMoveCallback::performTime(TimeEventData& data) {
   if (getPercentageDone() == 0.0) {
      mStartPosition = mEntity->getTranslation();
   }
   mTimePassed += data.mTimePassed;
   mEntity->moveTo(mStartPosition + ease(getPercentageDone()) * mEndPosition);
}

} /* actions */
} /* fillwave */
