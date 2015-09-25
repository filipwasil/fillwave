/*
 * FollowCustomCursorCallback.h
 *
 *  Created on: Nov 8, 2014
 *      Author: filip
 */

#ifndef FOLLOWCUSTOMCURSORCALLBACK_H_
#define FOLLOWCUSTOMCURSORCALLBACK_H_

#include <fillwave/actions/EngineCallback.h>
#include <fillwave/actions/Event.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
   class Engine;
namespace actions {

/*! \class FollowCustomCursorCallback
 *
 * \brief EngineCallback to change follow the user created custom cursor.
 *
 */

class FollowCustomCursorCallback: public EngineCallback {
public:
   FollowCustomCursorCallback();
   virtual ~FollowCustomCursorCallback();
   void perform (Engine* engine, EventType* event);
   };

} /* particles */
} /* fillwave */

#endif /* FOLLOWCUSTOMCURSORCALLBACK_H_ */
