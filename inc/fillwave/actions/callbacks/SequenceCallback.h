/*
 * SequenceCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef SEQUENCECALLBACK_H_
#define SEQUENCECALLBACK_H_

#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/events/TimeTEvent.h>

#include <vector>

namespace fillwave {
namespace framework {

/*! \class SequenceCallback
 * \brief ItemCallback to execute an ordered vector of callbacks.
 */

class SequenceCallback: public Callback, public std::vector<puCallback> {
 public:
	SequenceCallback();
	virtual ~SequenceCallback() = default;

	/*	perform
	 * \brief Performs ItemCallback action
	 */

	void perform(EventType& eventType);

 protected:
	std::vector<puCallback>::iterator mCallbackIterator;
	bool mReloaditerator;
};

} /* framework */
typedef std::unique_ptr<framework::SequenceCallback> puSequenceCallback;
} /* fillwave */

#endif /* SEQUENCECALLBACK_H_ */
