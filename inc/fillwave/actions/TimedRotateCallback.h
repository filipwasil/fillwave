/*
 * TimedRotateCallback.h
 *
 *  Created on: 13 May 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#ifndef ROTATECALLBACK_H_
#define ROTATECALLBACK_H_

#include <fillwave/actions/TimedCallback.h>
#include <fillwave/models/Entity.h>

namespace fillwave {
namespace actions {

/*! \class TimedRotateCallback
 *
 * \brief TimedCallback to rotate Entity at certain angle in certain time.
 *
 */

class TimedRotateCallback: public TimedCallback {
public:
	TimedRotateCallback(
			pEntity entity,
			glm::vec3 axis,
			GLfloat angle,
			GLfloat lifeTime,
			eEasing easing = eEasing::None);
	virtual ~TimedRotateCallback();

	/*
	 * perform
	 *
	 * \brief Performs ItemCallback action
	 */

	void performTime(TimeEventData& data);

protected:
	pEntity mEntity;

private:
	glm::quat mStartRotation;
	GLfloat mStartAngle;
	GLfloat mEndAngle;
	glm::vec3 mAxis;
};

} /* actions */
} /* fillwave */

#endif /* ROTATECALLBACK_H_ */
