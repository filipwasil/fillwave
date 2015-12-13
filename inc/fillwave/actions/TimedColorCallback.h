/*
 * TimedColorCallback.h
 *
 *  Created on: 11 lut 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_ACTIONS_TIMEDCOLORCALLBACK_H_
#define INC_FILLWAVE_ACTIONS_TIMEDCOLORCALLBACK_H_

#include <fillwave/actions/TimedCallback.h>
#include <fillwave/models/Model.h>
#include <fillwave/effects/Painter.h>

namespace fillwave {
namespace actions {

/*! \class TimedColorCallback
 * \brief TimedCallback to change Entity color in time.
 */

class TimedColorCallback: public TimedCallback {
public:
	TimedColorCallback(
			pModel model,
			glm::vec4 endColor,
			GLfloat lifeTime,
			EasingFunction easing);

	virtual ~TimedColorCallback() = default;

	/*	perform
	 * \brief Performs ItemCallback action
	 */

	void perform(EventType& eventType);

private:
	glm::vec4 mStartColor;
	glm::vec4 mEndColor;
	pModel mModel;
	pPainter mPainter;
};

} /* actions */
} /* fillwave */

#endif /* INC_FILLWAVE_ACTIONS_TIMEDCOLORCALLBACK_H_ */
