/*
 * TimedColorCallback.h
 *
 *  Created on: 11 lut 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_ACTIONS_TIMEDCOLORCALLBACK_H_
#define INC_FILLWAVE_ACTIONS_TIMEDCOLORCALLBACK_H_

#include <fillwave/actions/callbacks/TimedCallback.h>
#include <fillwave/models/Model.h>
#include <fillwave/models/effects/Painter.h>

namespace fillwave {
namespace framework {

/*! \class TimedColorCallback
 * \brief TimedCallback to change Entity color in time.
 */

class TimedColorCallback: public TimedCallback {
 public:
	TimedColorCallback(
	   Model* model,
	   glm::vec4 endColor,
	   GLfloat lifeTime,
	   EasingFunction easing);

	~TimedColorCallback() = default;

 private:
	glm::vec4 mStartColor;
	glm::vec4 mEndColor;
	Model* mModel;
	pPainter mPainter;
};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_ACTIONS_TIMEDCOLORCALLBACK_H_ */
