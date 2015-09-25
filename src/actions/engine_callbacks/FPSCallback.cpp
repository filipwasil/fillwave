/*
 * TextRefresheCallback.cpp
 *
 *  Created on: Nov 1, 2014
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

#include <fillwave/actions/FPSCallback.h>
#include <fillwave/Fillwave.h>
#include <fillwave/extras/Log.h>

FLOGINIT("FPSCallback", FERROR | FFATAL)

namespace fillwave {
namespace actions {

FPSCallback::FPSCallback(pText text)
		: EngineCallback(eEventType::time), mTimePassed(0.0), mText(text) {

}

FPSCallback::~FPSCallback() {

}

void FPSCallback::perform(Engine* engine, EventType* event) { //xxx make this more generic
	TimeEventData e = TimeEvent::getData(event);
	if (mTimePassed < 1.0) {
		mTimePassed += e.mTimePassed;
	} else {
		mTimePassed -= 1.0;
		mText->editString(
				std::string("FPS ")
						+ strings::to_string<GLuint>(engine->getFramesPassed()));
	}
}

} /* actions */
} /* fillwave */
