/*
 * TimedBoneUpdateCallback.h
 *
 *  Created on: 2 Jul 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDBONEUPDATECALLBACK_H_
#define TIMEDBONEUPDATECALLBACK_H_

#include <fillwave/actions/TimedCallback.h>

namespace fillwave {
namespace models {
class Model;
}

namespace actions {

/*! \class TimedBoneUpdateCallback
 * \brief TimedCallback to update animation keys.
 * It will be attached to every model containing animations.
 */

class TimedBoneUpdateCallback: public TimedCallback {
public:
	TimedBoneUpdateCallback(models::Model* model);
	virtual ~TimedBoneUpdateCallback();

	/*	perform
	 * \brief Performs ItemCallback action
	 */
	void performTime(TimeEventData& data);

protected:
	models::Model* mModel;
};

} /* actions */
} /* fillwave */

#endif /* TIMEDBONEUPDATECALLBACK_H_ */
