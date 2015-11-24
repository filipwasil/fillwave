/*
 * TimedMoveCallbackCustom.cpp
 *
 *  Created on: 16 Feb 2015
 *      Author: filip
 */

#include "../../../android/inc/CallbacksEGL/TimedMoveCallbackCustom.h"

#include <fillwave/common/Easing.h>

namespace fillwave {
namespace actions {

TimedMoveCallbackCustom::TimedMoveCallbackCustom(pMoveable moveable,
                                                 glm::vec3 endPosition,
                                                 GLfloat lifeTime):TimedMoveCallback(moveable, endPosition,lifeTime, eEasing::eCustom) {

}

TimedMoveCallbackCustom::~TimedMoveCallbackCustom() {

}

GLfloat TimedMoveCallbackCustom::easeCustom(GLfloat progress) {
   return QuinticEaseIn(progress)*QuinticEaseIn(progress);
}

} /* actions */
} /* fillwave */
