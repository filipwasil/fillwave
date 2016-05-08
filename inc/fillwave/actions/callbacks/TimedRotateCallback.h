/*
 * TimedRotateCallback.h
 *
 *  Created on: 13 May 2014
 *      Author: Filip Wasil
 */

#ifndef ROTATECALLBACK_H_
#define ROTATECALLBACK_H_

#include <fillwave/actions/callbacks/TimedCallback.h>

namespace fillwave {
namespace framework {

/*! \class TimedRotateCallback
 * \brief TimedCallback to rotate Entity at certain angle in certain time.
 */

class TimedRotateCallback: public TimedCallback {
 public:
	TimedRotateCallback(
	   Moveable* moveable,
	   glm::vec3 axis,
	   GLfloat angle,
	   GLfloat lifeTime,
	   EasingFunction easing = LinearInterpolation);

	~TimedRotateCallback() = default;

 protected:
	Moveable* mMoveable;

 private:
	glm::quat mStartRotation;
	GLfloat mStartAngle;
	GLfloat mEndAngle;
	glm::vec3 mAxis;
};

} /* framework */
} /* fillwave */

#endif /* ROTATECALLBACK_H_ */
