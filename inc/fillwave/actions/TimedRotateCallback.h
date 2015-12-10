/*
 * TimedRotateCallback.h
 *
 *  Created on: 13 May 2014
 *      Author: Filip Wasil
 */

#ifndef ROTATECALLBACK_H_
#define ROTATECALLBACK_H_

#include <fillwave/actions/TimedCallback.h>

namespace fillwave {
namespace actions {

/*! \class TimedRotateCallback
 * \brief TimedCallback to rotate Entity at certain angle in certain time.
 */

class TimedRotateCallback: public TimedCallback {
public:
	TimedRotateCallback(
			pMoveable moveable,
			glm::vec3 axis,
			GLfloat angle,
			GLfloat lifeTime,
			EasingFunction easing = LinearInterpolation);

	virtual ~TimedRotateCallback() = default;

	void performTime(TimeEventData& data);

protected:
	pMoveable mMoveable;

private:
	glm::quat mStartRotation;
	GLfloat mStartAngle;
	GLfloat mEndAngle;
	glm::vec3 mAxis;
};

} /* actions */
} /* fillwave */

#endif /* ROTATECALLBACK_H_ */
