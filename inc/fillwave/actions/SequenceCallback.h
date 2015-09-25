/*
 * SequenceCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef SEQUENCECALLBACK_H_
#define SEQUENCECALLBACK_H_

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

#include <fillwave/actions/ItemCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/actions/Callback.h>

#include <vector>

namespace fillwave {
namespace actions {

/*! \class SequenceCallback
 *
 * \brief ItemCallback to execute an ordered vector of callbacks.
 *
 */

class SequenceCallback: public ItemCallback, public std::vector<ItemCallback*> {
public:
	SequenceCallback();
	virtual ~SequenceCallback();

	/*
	 * perform
	 *
	 * \brief Performs ItemCallback action
	 */

	void perform(EventType* eventType);

protected:
	std::vector<ItemCallback*>::iterator mCallbackIterator;
	bool mReloaditerator;
};

} /* actions */
} /* fillwave */

#endif /* SEQUENCECALLBACK_H_ */
