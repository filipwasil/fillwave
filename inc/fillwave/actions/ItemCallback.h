/*
 * ItemCallback.h
 *
 *  Created on: 8 May 2014
 *      Author: Filip Wasil
 */

#ifndef ITEMCALLBACK_H_
#define ITEMCALLBACK_H_

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
#include <fillwave/actions/Event.h>
#include <fillwave/actions/Callback.h>

namespace fillwave {
namespace actions {

/*! \class ItemCallback
 *
 * \brief Base for item callbacks.
 *
 */

class ItemCallback: public common::Finishable, public Callback {
public:
	ItemCallback(eEventType eventType, float timeToFinish = FILLWAVE_ENDLESS)
			: Finishable(timeToFinish), Callback(eventType), mEnabled(true) {
	}

	virtual void perform(EventType* event) = 0;

	~ItemCallback() {

	}

	bool isEnabled() {
		return mEnabled;
	}

	void enable() {
		mEnabled = true;
	}

	void disable() {
		mEnabled = false;
	}

protected:
	bool mEnabled;
};

} /* actions */
} /* fillwave */

#endif /* ITEMCALLBACK_H_ */
