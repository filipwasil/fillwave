/*
 * TimedBoneUpdateCallback.h
 *
 *  Created on: 2 Jul 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDBONEUPDATECALLBACK_H_
#define TIMEDBONEUPDATECALLBACK_H_

#include <fillwave/actions/callbacks/TimedCallback.h>

namespace fillwave {
namespace framework {
class Model;

/*! \class TimedBoneUpdateCallback
 * \brief TimedCallback to update animation keys.
 * It will be attached to every model containing animations.
 */

class TimedBoneUpdateCallback: public TimedCallback {
public:
	TimedBoneUpdateCallback(Model* model);
	virtual ~TimedBoneUpdateCallback() = default;

	/*	perform
	 * \brief Performs ItemCallback action
	 */
	void performTime(TimeEventData& data);

protected:
	Model* mModel;
};

} /* framework */
} /* fillwave */

#endif /* TIMEDBONEUPDATECALLBACK_H_ */
