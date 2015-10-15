/*
 * TimedMoveCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDMOVECALLBACK_H_
#define TIMEDMOVECALLBACK_H_

#include <fillwave/actions/TimedCallback.h>
#include <fillwave/models/Entity.h>
#include <fillwave/Math.h>

namespace fillwave {
namespace actions {

/*! \class TimedMoveCallback
 * \brief TimedCallback to move Entity at certain distance in certain time.
 */

class TimedMoveCallback: public TimedCallback {
public:
	TimedMoveCallback(
			pEntity entity,
			glm::vec3 endPosition,
			GLfloat lifeTime,
			eEasing easing = eEasing::None);

	virtual ~TimedMoveCallback() = default;

	/*	perform
	 * \brief Performs ItemCallback action
	 */

	void performTime(TimeEventData& data);

protected:
	glm::vec3 mStartPosition;
	glm::vec3 mEndPosition;
	pEntity mEntity;
};

} /* actions */
} /* fillwave */

#endif /* TIMEDMOVECALLBACK_H_ */
