/*
 * Callback.h
 *
 *  Created on: Oct 2, 2014
 *      Author: Filip Wasil
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

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
