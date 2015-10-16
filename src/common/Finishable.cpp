/*
 * Finishable.cpp
 *
 *  Created on: Sep 16, 2014
 *      Author: filip
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

void Finishable::checkTime(float timePassed) {
	mTimePassed += timePassed;
	if (mTimePassed > mTimeToFinish && mTimeToFinish != FILLWAVE_ENDLESS) {
		mTimePassed -= mTimeToFinish;
		finish();
	}
}

float Finishable::getPercentageDone() const {
	return mTimePassed / mTimeToFinish >= 1.0 ? 1.0 : mTimePassed / mTimeToFinish;
}

void Finishable::finish() {
	mFinished = true;
}

void Finishable::reset() {
	mFinished = false;
}

bool Finishable::isFinished() const {
	return mFinished;
}

} /* common */
} /* fillwave */
