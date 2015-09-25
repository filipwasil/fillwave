/*
 * Finishable.cpp
 *
 *  Created on: Sep 16, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
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

#include <fillwave/common/Finishable.h>

namespace fillwave {
namespace common {

Finishable::Finishable(float timeToFinish)
		:
				mFinished(false),
				mTimeToFinish(timeToFinish),
				mTimePassed(0),
				mPercentageDone(0) {

}

Finishable::~Finishable() {

}

void Finishable::checkTime(float timePassed) {
	mTimePassed += timePassed;
	if (mTimePassed > mTimeToFinish && mTimeToFinish != FILLWAVE_ENDLESS) {
		mTimePassed -= mTimeToFinish;
		finish();
	}
}

float Finishable::getPercentageDone() {
	return mTimePassed / mTimeToFinish >= 1.0 ? 1.0 : mTimePassed / mTimeToFinish;
}

void Finishable::finish() {
	mFinished = true;
}

void Finishable::reset() {
	mFinished = false;
}

bool Finishable::isFinished() {
	return mFinished;
}

} /* common */
} /* fillwave */
