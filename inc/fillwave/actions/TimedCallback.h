/*
 * TimedCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDCALLBACK_H_
#define TIMEDCALLBACK_H_

#include <fillwave/OpenGL.h>
#include <fillwave/actions/ItemCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/models/Moveable.h>
#include <fillwave/common/Easing.h>

namespace fillwave {
namespace actions {

/*! \class TimedCallback
 *
 * \brief ItemCallback to be finished after a period of time.
 *
 */

class TimedCallback: public ItemCallback {
public:
	TimedCallback(GLfloat timeToFinish, EasingFunction funcion = LinearInterpolation);

	virtual ~TimedCallback() = default;

	/*	perform
	 * \brief Performs ItemCallback action.
	 */

	void perform(EventType* eventType);

	virtual void performTime(TimeEventData& e);

	GLfloat ease(GLfloat progress);

private:
	EasingFunction mEasing;
};

} /* actions */
} /* fillwave */

#endif /* TIMEDCALLBACK_H_ */

