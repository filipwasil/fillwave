/*
 * EngineCallback.h
 *
 *  Created on: Jun 21, 2014
 *      Author: Filip Wasil
 */

#ifndef ENGINECALLBACK_H_
#define ENGINECALLBACK_H_

#include <fillwave/actions/Callback.h>

namespace fillwave {
class Engine;
namespace actions {
class EventType;

/*! \class EngineCallback
 * \brief Base for engine-aware callbacks.
 */

class EngineCallback: public Callback {
public:
	EngineCallback(eEventType eventType)
			: Callback(eventType) {

	}

	virtual ~EngineCallback() = default;

/*	perform
 * \brief virtual: Performs EngineCallback action
 */

	virtual void perform(Engine* engine, EventType* eventType) = 0;
};

} /* actions */
} /* fillwave */

#endif /* ENGINECALLBACK_H_ */
