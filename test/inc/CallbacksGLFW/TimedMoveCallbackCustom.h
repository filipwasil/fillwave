/*
 * TimedMoveCallbackCustom.h
 *
 *  Created on: 16 Feb 2015
 *      Author: filip
 */

#ifndef TIMEDMOVECALLBACKCUSTOM_H_
#define TIMEDMOVECALLBACKCUSTOM_H_

#include <fillwave/actions/TimedMoveCallback.h>

namespace fillwave {
namespace actions {

class TimedMoveCallbackCustom: public fillwave::actions::TimedMoveCallback {
public:
   TimedMoveCallbackCustom(pEntity entity,
                           glm::vec3 endPosition,
                           GLfloat lifeTime);
   virtual ~TimedMoveCallbackCustom();
   GLfloat easeCustom(GLfloat progress);
};

} /* actions */
} /* fillwave */

#endif /* TIMEDMOVECALLBACKCUSTOM_H_ */
