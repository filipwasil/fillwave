/*
 * TimeStopCallback.h
 *
 *  Created on: 15 sty 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_TIMESTOPCALLBACK_H_
#define INC_FILLWAVE_TIMESTOPCALLBACK_H_

#include <fillwave/Framework.h>

namespace fillwave {
class Engine;
namespace framework {

class TimeStopCallback: public Callback {
 public:
	TimeStopCallback(Engine* engine);
	~TimeStopCallback() = default;
 private:
	bool mTimeOn;
	Engine* mEngine;
};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_TIMESTOPCALLBACK_H_ */
