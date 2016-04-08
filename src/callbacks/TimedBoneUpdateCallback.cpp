/*
 * TimedBoneUpdateCallback.cpp
 *
 *  Created on: 2 Jul 2014
 *
 */

#include <fillwave/actions/callbacks/TimedBoneUpdateCallback.h>
#include <fillwave/actions/events/TimeTEvent.h>
#include <fillwave/models/Model.h>
#include <fillwave/Log.h>

FLOGINIT("TimedBoneUpdateCallback", FERROR | FFATAL)

namespace fillwave {
namespace framework {

TimedBoneUpdateCallback::TimedBoneUpdateCallback(Model* model) :
	TimedCallback(0.0), mModel(model) {
	FLOG_DEBUG("Added animation callback");
}

void TimedBoneUpdateCallback::performTime(TimeEventData& data) {
	mModel->performAnimation(data.mTimePassed);
}

} /* framework */
} /* fillwave */
