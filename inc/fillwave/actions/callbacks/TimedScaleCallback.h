/*
 * TimedScaleCallback.h
 *
 *  Created on: 15 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDSCALECALLBACK_H_
#define TIMEDSCALECALLBACK_H_

#include <fillwave/actions/callbacks/TimedCallback.h>
#include <fillwave/models/base/Moveable.h>

namespace fillwave {
namespace framework {

/*! \class TimedScaleCallback
 * \brief TimedCallback to scale the Entity to certain size in certain time.
 */

class TimedScaleCallback: public TimedCallback {
 public:
	TimedScaleCallback(
	   Moveable* moveable,
	   glm::vec3 normalizedScaleVec,
	   GLfloat lifetime,
	   EasingFunction easing = LinearInterpolation);
	TimedScaleCallback(
	   Moveable* moveable,
	   GLfloat normalizedScale,
	   GLfloat lifetime,
	   EasingFunction easing = LinearInterpolation);

	~TimedScaleCallback() = default;

 protected:
	glm::vec3 mStartScale;
	glm::vec3 mEndScale;
	Moveable* mMoveable;
};

} /* framework */
} /* fillwave */

#endif /* TIMEDSCALECALLBACK_H_ */
