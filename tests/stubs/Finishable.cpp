/*
 * Template.cpp
 *
 *  Created on: Jan 31, 2016
 *      Author: filip
 */

#include <fillwave/Log.h>
#include <fillwave/common/Finishable.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

FLOGINIT_DEFAULT()

namespace fillwave {
namespace framework {

Finishable::Finishable(float) : mFinished(false) {

}

float Finishable::getPercentageDone() const {
	return
	   mTimePassed / mTimeToFinish >= 1.0f ?
	   1.0f : mTimePassed / mTimeToFinish;
}

}
}
