/*
 * TimedEmiterUpdateCallback.h
 *
 *  Created on: Nov 9, 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDEMITERUPDATECALLBACK_H_
#define TIMEDEMITERUPDATECALLBACK_H_

#include <fillwave/actions/callbacks/TimedCallback.h>
#include <fillwave/models/EmiterPointCPU.h>

namespace fillwave {
namespace framework {

/*! \class TimedEmiterUpdateCallback
 * \brief TimedCallback to update time in emiters.
 */

class TimedEmiterUpdateCallback: public TimedCallback {
  public:
	TimedEmiterUpdateCallback(
	    pIEmiterPoint emiter,
	    GLfloat timeToFinish,
	    EasingFunction easing = LinearInterpolation);

	virtual ~TimedEmiterUpdateCallback() = default;

	void performTime(TimeEventData& data);

  protected:
	pIEmiterPoint mEmiter;

  private:
	GLfloat mTimePassed;
};

} /* framework */
} /* fillwave */

#endif /* TIMEDEMITERUPDATECALLBACK_H_ */
