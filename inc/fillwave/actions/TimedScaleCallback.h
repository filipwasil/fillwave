/*
 * TimedScaleCallback.h
 *
 *  Created on: 15 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDSCALECALLBACK_H_
#define TIMEDSCALECALLBACK_H_

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

/*! \class TimedScaleCallback
 *
 * \brief TimedCallback to scale the Entity to certain size in certain time.
 *
 */

class TimedScaleCallback: public TimedCallback {
public:
    TimedScaleCallback(pEntity entity, glm::vec3 normalizedScaleVec, GLfloat lifetime, eEasing easing);
    TimedScaleCallback(pEntity entity, GLfloat normalizedScale, GLfloat lifetime, eEasing easing);
    virtual ~TimedScaleCallback();

    /*
     * perform
     *
     * \brief scales the entity with specified size gradient in specified time
     *
     */

    void performTime(TimeEventData& data);

protected:
    glm::vec3 mStartScale;
    glm::vec3 mEndScale;
    pEntity mEntity;
};

} /* actions */
} /* fillwave */
#endif /* TIMEDSCALECALLBACK_H_ */
