/*
 * TimedBoneUpdateCallback.cpp
 *
 *  Created on: 2 Jul 2014
 *
 */

#include <fillwave/actions/TimedBoneUpdateCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/models/Model.h>
#include <fillwave/extras/Log.h>

FLOGINIT("TimedBoneUpdateCallback", FERROR | FFATAL)

namespace fillwave {
namespace actions {

TimedBoneUpdateCallback::TimedBoneUpdateCallback(models::Model* model)
		: TimedCallback(0.0), mModel(model) {
	FLOG_DEBUG("Added animation callback");
}

void TimedBoneUpdateCallback::performTime(TimeEventData& data) {
	mModel->performAnimation(data.mTimePassed);
}

} /* actions */
} /* fillwave */
