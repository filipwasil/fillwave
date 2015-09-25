/*
 * TimedRotateCallback.cpp
 *
 *  Created on: 13 May 2014
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

#include <fillwave/actions/TimedRotateCallback.h>
#include <fillwave/actions/KeyboardEvent.h>
#include <fillwave/actions/TimeEvent.h>

#include <fillwave/Math.h>

#include <iostream>

namespace fillwave {
namespace actions {

TimedRotateCallback::TimedRotateCallback(
		pEntity entity,
		glm::vec3 axis,
		GLfloat angle,
		GLfloat lifeTime,
		eEasing easing)
		:
				TimedCallback(lifeTime, easing),
				mStartRotation(glm::quat()),
				mStartAngle(0.0),
				mEndAngle(angle),
				mAxis(axis),
				mEntity(entity) {

}

TimedRotateCallback::~TimedRotateCallback() {

}

void TimedRotateCallback::performTime(TimeEventData& data) {
	if (getPercentageDone() == 0.0) {
		mStartRotation = mEntity->getRotation();
	}
	mTimePassed += data.mTimePassed;
	mEntity->rotateTo(mStartRotation);
	mEntity->rotateBy(mAxis,
			mStartAngle + ease(getPercentageDone()) * mEndAngle);
}

} /* actions */
} /* fillwave */
