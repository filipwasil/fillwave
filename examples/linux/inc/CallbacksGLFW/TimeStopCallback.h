/*
 * TimeStopCallback.h
 *
 *  Created on: 15 sty 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_TIMESTOPCALLBACK_H_
#define INC_FILLWAVE_TIMESTOPCALLBACK_H_

#include <fillwave/actions/Callback.h>
#include <fillwave/actions/Event.h>

namespace fillwave {
class Engine;
namespace actions {

class TimeStopCallback: public Callback {
public:
   TimeStopCallback(Engine* engine);
   virtual ~TimeStopCallback();
   void perform(EventType& event);
private:
   bool mTimeOn;
   Engine* mEngine;
};

} /* actions */
} /* fillwave */

#endif /* INC_FILLWAVE_TIMESTOPCALLBACK_H_ */
