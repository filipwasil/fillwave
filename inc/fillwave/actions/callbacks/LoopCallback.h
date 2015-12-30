/*
 * LoopCallback.h
 *
 *  Created on: 12 May 2014
 *      Author: Filip Wasil
 */

#ifndef LOOPCALLBACK_H_
#define LOOPCALLBACK_H_

#include <fillwave/common/Finishable.h>

#include <fillwave/actions/events/Event.h>
#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/callbacks/Callback.h>

#define ENDLESS_LOOP 0

namespace fillwave {
namespace framework {

/*! \class LoopCallback
 * \brief ItemCallback to loop other callbacks.
 */

class LoopCallback: public Callback {
public:
	LoopCallback(Callback* callback, int numberOfExecutions);
	virtual ~LoopCallback() = default;

	/*	perform
	 * \brief Performs ItemCallback action.
	 */

	void perform(EventType& event);

protected:
	puCallback mCallback;
	int mLoopsLeft;
};

} /* framework */
} /* fillwave */

#endif /* LOOPCALLBACK_H_ */
