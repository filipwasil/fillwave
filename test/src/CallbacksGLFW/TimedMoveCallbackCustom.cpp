/*
 * TimedMoveCallbackCustom.cpp
 *
 *  Created on: 16 Feb 2015
 *      Author: filip
 */

#include <CallbacksGLFW/TimedMoveCallbackCustom.h>
#include <fillwave/common/Easing.h>

namespace fillwave {
namespace actions {


TimedMoveCallbackCustom::TimedMoveCallbackCustom(pEntity entity,
                                                 glm::vec3 endPosition,
                                                 GLfloat lifeTime):TimedMoveCallback(entity, endPosition,lifeTime, eEasing::Custom) {

}

TimedMoveCallbackCustom::~TimedMoveCallbackCustom() {

}

GLfloat TimedMoveCallbackCustom::easeCustom(GLfloat progress) {
   return QuinticEaseIn(progress)*QuinticEaseIn(progress);
}

} /* actions */
} /* fillwave */
