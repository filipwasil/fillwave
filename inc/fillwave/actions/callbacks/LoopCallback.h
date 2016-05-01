/*
 * LoopCallback.h
 *
 *  Created on: 12 May 2014
 *      Author: Filip Wasil
 */

#ifndef LOOPCALLBACK_H_
#define LOOPCALLBACK_H_

#include <fillwave/common/Finishable.h>

#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/events/TEvent.h>

namespace fillwave {
namespace framework {

/*! \class LoopCallback
 * \brief ItemCallback to loop other callbacks.
 */

class LoopCallback: public Callback {
 public:
	LoopCallback(puCallback&& callback, int numberOfExecutions);
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
typedef std::unique_ptr<framework::LoopCallback> puLoopCallback;
} /* fillwave */

#endif /* LOOPCALLBACK_H_ */
