/*
 * TimedColorCallback.cpp
 *
 *  Created on: 11 lut 2015
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
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/actions/TimedColorCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/extras/Log.h>

namespace fillwave {
namespace actions {

TimedColorCallback::TimedColorCallback(pModel model,
                                       glm::vec4 endColor,
                                       GLfloat lifeTime,
                                       eEasing easing)
:TimedCallback(lifeTime, easing),
 mStartColor (glm::vec4(0.0)),
 mEndColor (endColor),
 mModel(model) {
   mPainter = pPainter( new effects::Painter(mStartColor));
   mModel->addEffect(mPainter);
}

TimedColorCallback::~TimedColorCallback() {

}

void TimedColorCallback::perform(EventType* event) {
   TimeEventData myData = TimeEvent::getData(event);
   if (getPercentageDone() == 0.0) {
      mPainter->setColor(mStartColor);
   }
   mTimePassed += myData.mTimePassed;
   mPainter->setColor(mStartColor + ease(getPercentageDone()) * mEndColor);
   checkTime(myData.mTimePassed);
   if (mFinished) {
      mModel->removeEffect(mPainter);
   }
}


} /* actions */
} /* fillwave */

