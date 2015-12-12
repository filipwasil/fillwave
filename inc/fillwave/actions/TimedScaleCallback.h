/*
 * TimedScaleCallback.h
 *
 *  Created on: 15 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDSCALECALLBACK_H_
#define TIMEDSCALECALLBACK_H_

#include <fillwave/actions/TimedCallback.h>

namespace fillwave {
namespace actions {

/*! \class TimedScaleCallback
 * \brief TimedCallback to scale the Entity to certain size in certain time.
 */

class TimedScaleCallback: public TimedCallback {
public:
	TimedScaleCallback(
			pMoveable moveable,
			glm::vec3 normalizedScaleVec,
			GLfloat lifetime,
			EasingFunction easing = LinearInterpolation);
	TimedScaleCallback(
			pMoveable moveable,
			GLfloat normalizedScale,
			GLfloat lifetime,
			EasingFunction easing = LinearInterpolation);

	virtual ~TimedScaleCallback() = default;

	void performTime(TimeEventData& data);

protected:
	glm::vec3 mStartScale;
	glm::vec3 mEndScale;
	pMoveable mMoveable;
};

} /* actions */
} /* fillwave */
#endif /* TIMEDSCALECALLBACK_H_ */
