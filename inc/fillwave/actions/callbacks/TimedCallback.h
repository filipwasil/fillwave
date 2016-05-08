/*
 * TimedCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDCALLBACK_H_
#define TIMEDCALLBACK_H_

#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/events/TimeTEvent.h>
#include <fillwave/common/Easing.h>
#include <fillwave/models/base/Moveable.h>
#include <fillwave/OpenGL.h>

namespace fillwave {
namespace framework {

	typedef std::function<void(TimeEventData&)> TimeFunction;
/*! \class TimedCallback
 * \brief ItemCallback to be finished after a period of time.
 */

class TimedCallback: public Callback {
 public:
	TimedCallback(GLfloat timeToFinish, TimeFunction foo = TimeFunction(), EasingFunction funcion =
	                 LinearInterpolation);

	~TimedCallback() = default;

	GLfloat ease(GLfloat progress);

 private:
	EasingFunction mEasing;
	TimeFunction mTime;
};

} /* framework */
} /* fillwave */

#endif /* TIMEDCALLBACK_H_ */

