/*
 * TimedColorCallback.h
 *
 *  Created on: 11 lut 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_ACTIONS_TIMEDCOLORCALLBACK_H_
#define INC_FILLWAVE_ACTIONS_TIMEDCOLORCALLBACK_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/actions/TimedCallback.h>
#include <fillwave/models/Model.h>
#include <fillwave/effects/Painter.h>

namespace fillwave {
namespace actions {

/*! \class TimedColorCallback
 *
 * \brief TimedCallback to change Entity color in time.
 *
 */

class TimedColorCallback: public TimedCallback {
public:
	TimedColorCallback(
			pModel model,
			glm::vec4 endColor,
			GLfloat lifeTime,
			eEasing easing);
	virtual ~TimedColorCallback();

	/*
	 * perform
	 *
	 * \brief Performs ItemCallback action
	 */

	void perform(EventType* eventType);

private:
	glm::vec4 mStartColor;
	glm::vec4 mEndColor;
	pModel mModel;
	pPainter mPainter;
};

} /* actions */
} /* fillwave */

#endif /* INC_FILLWAVE_ACTIONS_TIMEDCOLORCALLBACK_H_ */
