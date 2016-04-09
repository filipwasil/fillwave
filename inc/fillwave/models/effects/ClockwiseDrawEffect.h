/*
 * ClockwiseDrawEffect.h
 *
 *  Created on: 24 Jul 2014
 *      Author: Filip Wasil
 */

#ifndef CLOCKWISEDRAWEFFECT_H_
#define CLOCKWISEDRAWEFFECT_H_

#include <fillwave/models/effects/Effect.h>

namespace fillwave {
namespace framework {

/*! \class ClockwiseDrawEffect
 * \brief Effect to draw an opposite face of each mesh.
 */

class ClockwiseDrawEffect: public IEffect {
 public:
	ClockwiseDrawEffect() = default;
	virtual ~ClockwiseDrawEffect() = default;

	void preDrawAction(core::Program* program);
	void postDrawAction(core::Program* program);
	void stopAction(core::Program* program);
	void startAction(core::Program* program);
};

} /* framework */
} /* fillwave */

#endif /* CLOCKWISEDRAWEFFECT_H_ */
