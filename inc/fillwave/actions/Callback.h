/*
 * Callback.h
 *
 *  Created on: Oct 2, 2014
 *      Author: Filip Wasil
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/actions/EventType.h>

namespace fillwave {
namespace actions {

/*! \class Callback
 *
 * \brief Base for all callbacks.
 *
 */

class Callback {
public:
	Callback(eEventType eventType)
			: mEventSupportedType(eventType) {

	}
	;

	virtual ~Callback() {

	}
	;

	eEventType getSupportedEventType() {
		return mEventSupportedType;
	}
	;

private:
	eEventType mEventSupportedType;
};

} /* actions */
} /* fillwave */

#endif /* CALLBACK_H_ */
