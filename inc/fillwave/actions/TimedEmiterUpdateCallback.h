/*
 * TimedEmiterUpdateCallback.h
 *
 *  Created on: Nov 9, 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDEMITERUPDATECALLBACK_H_
#define TIMEDEMITERUPDATECALLBACK_H_

#include <fillwave/actions/TimedCallback.h>
#include <fillwave/particles/EmiterPointCPU.h>

namespace fillwave {
namespace actions {

/*! \class TimedEmiterUpdateCallback
 *
 * \brief TimedCallback to update time in emiters.
 *
 */

class TimedEmiterUpdateCallback: public TimedCallback {
public:
   TimedEmiterUpdateCallback(pEmiterPoint emiter,
                             GLfloat timeToFinish,
                             eEasing easing = eEasing::None);

   virtual ~TimedEmiterUpdateCallback();

   void performTime(TimeEventData& data);

protected:
   pEmiterPoint mEmiter;

private:
   GLfloat mTimePassed;
};

} /* actions */
} /* fillwave */

#endif /* TIMEDEMITERUPDATECALLBACK_H_ */
