/*
 * TimedMoveCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDMOVECALLBACK_H_
#define TIMEDMOVECALLBACK_H_

#include <fillwave/actions/callbacks/TimedCallback.h>
#include <fillwave/models/base/Moveable.h>
#include <fillwave/Math.h>

namespace fillwave {
namespace framework {

/*! \class TimedMoveCallback
 * \brief TimedCallback to move Entity at certain distance in certain time.
 */

class TimedMoveCallback: public TimedCallback {
 public:
	TimedMoveCallback(
	   Moveable* moveable,
	   glm::vec3 endPosition,
	   GLfloat lifeTime,
	   EasingFunction easing = LinearInterpolation);

	~TimedMoveCallback() = default;

 protected:
	glm::vec3 mStartPosition;
	glm::vec3 mEndPosition;
	Moveable* mMoveable;
};

} /* framework */
} /* fillwave */

#endif /* TIMEDMOVECALLBACK_H_ */
