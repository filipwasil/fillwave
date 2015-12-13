/*
 * FollowCustomCursorCallback.h
 *
 *  Created on: Nov 8, 2014
 *      Author: filip
 */

#ifndef FOLLOWCUSTOMCURSORCALLBACK_H_
#define FOLLOWCUSTOMCURSORCALLBACK_H_

#include <fillwave/actions/Callback.h>
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

class FollowCustomCursorCallback: public Callback {
public:
   FollowCustomCursorCallback(Engine* engine);
   virtual ~FollowCustomCursorCallback() = default;
   void perform (EventType& event);
private:
   Engine* mEngine;
   };

} /* particles */
} /* fillwave */

#endif /* FOLLOWCUSTOMCURSORCALLBACK_H_ */
