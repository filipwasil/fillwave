/*
 * TimedBoneUpdateCallback.cpp
 *
 *  Created on: 2 Jul 2014
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

TimedBoneUpdateCallback::~TimedBoneUpdateCallback() {

}

void TimedBoneUpdateCallback::performTime(TimeEventData& data) {
	mModel->performAnimation(data.mTimePassed);
}

} /* actions */
} /* fillwave */
