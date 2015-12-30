/*
 * TimedCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDCALLBACK_H_
#define TIMEDCALLBACK_H_

#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/events/TimeEvent.h>
#include <fillwave/common/Easing.h>
#include <fillwave/models/base/Moveable.h>
#include <fillwave/OpenGL.h>

namespace fillwave {
namespace framework {

/*! \class TimedCallback
 *
 * \brief ItemCallback to be finished after a period of time.
 *
 */

class TimedCallback: public Callback {
public:
	TimedCallback(GLfloat timeToFinish, EasingFunction funcion = LinearInterpolation);

	virtual ~TimedCallback() = default;

	/*	perform
	 * \brief Performs ItemCallback action.
	 */

	void perform(EventType& eventType);

	virtual void performTime(TimeEventData& e);

	GLfloat ease(GLfloat progress);

private:
	EasingFunction mEasing;
};

} /* framework */
} /* fillwave */

#endif /* TIMEDCALLBACK_H_ */

