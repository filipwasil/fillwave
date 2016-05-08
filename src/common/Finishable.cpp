/*
 * Finishable.cpp
 *
 *  Created on: Sep 16, 2014
 *      Author: filip
 */

#include <fillwave/common/Finishable.h>
namespace fillwave {
namespace framework {

Finishable::Finishable(float timeToFinish) :
	mFinished(false),
	mTimeToFinish(timeToFinish),
	mTimePassed(0),
	mPercentageDone(0) {

}

void Finishable::checkTime(float timePassed) {
	mTimePassed += timePassed;
	if (mTimePassed > mTimeToFinish && mTimeToFinish != FILLWAVE_ENDLESS) {
		mTimePassed -= mTimeToFinish;
		mFinished = true;
	}
}

float Finishable::getPercentageDone() const {
	return
	   mTimePassed / mTimeToFinish >= 1.0f ?
	   1.0f : mTimePassed / mTimeToFinish;
}

void Finishable::setFinished(bool state) {
	mFinished = state;
}

bool Finishable::getFinished() const {
	return mFinished;
}

} /* framework */
} /* fillwave */
