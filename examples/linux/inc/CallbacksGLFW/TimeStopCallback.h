/*
 * TimeStopCallback.h
 *
 *  Created on: 15 sty 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_TIMESTOPCALLBACK_H_
#define INC_FILLWAVE_TIMESTOPCALLBACK_H_

#include <fillwave/actions/EngineCallback.h>
#include <fillwave/actions/Event.h>

namespace fillwave {
class Engine;
namespace actions {

class TimeStopCallback: public EngineCallback {
private:
   bool mTimeOn;
public:
   TimeStopCallback();
   virtual ~TimeStopCallback();
   void perform(Engine* engine, EventType* event);
};

} /* actions */
} /* fillwave */

#endif /* INC_FILLWAVE_TIMESTOPCALLBACK_H_ */
