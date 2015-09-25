/*
 * LoopCallback.h
 *
 *  Created on: 12 May 2014
 *      Author: Filip Wasil
 */

#ifndef LOOPCALLBACK_H_
#define LOOPCALLBACK_H_

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

#include <fillwave/common/Finishable.h>

#include <fillwave/actions/ItemCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/actions/Callback.h>

#define ENDLESS_LOOP 0

namespace fillwave {
namespace actions {

/*! \class LoopCallback
 *
 * \brief ItemCallback to loop other callbacks.
 *
 */

class LoopCallback: public ItemCallback {
public:
	LoopCallback(ItemCallback* callback, int numberOfExecutions);
	virtual ~LoopCallback();

	/*
	 * perform
	 *
	 * \brief Performs ItemCallback action.
	 */

	void perform(EventType* event);

protected:
	ItemCallback* mItemCallback;
	int mLoopsLeft;
};

} /* actions */
} /* fillwave */

#endif /* LOOPCALLBACK_H_ */
