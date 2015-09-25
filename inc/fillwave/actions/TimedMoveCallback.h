/*
 * TimedMoveCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDMOVECALLBACK_H_
#define TIMEDMOVECALLBACK_H_

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
#include <fillwave/models/Entity.h>
#include <fillwave/Math.h>

namespace fillwave {
namespace actions {

/*! \class TimedMoveCallback
 *
 * \brief TimedCallback to move Entity at certain distance in certain time.
 *
 */

class TimedMoveCallback: public TimedCallback {
public:
    TimedMoveCallback(pEntity entity,
                      glm::vec3 endPosition,
                      GLfloat lifeTime,
                      eEasing easing = eEasing::None);
    virtual ~TimedMoveCallback();

    /*
     * perform
     *
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
