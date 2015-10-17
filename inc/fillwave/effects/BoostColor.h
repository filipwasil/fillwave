/*
 * BoostColor.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Filip Wasil
 */

#ifndef BOOSTCOLOR_H_
#define BOOSTCOLOR_H_

#include <fillwave/effects/Effect.h>

namespace fillwave {
namespace effects {

/*! \class BoostColor
 * \brief Effect to boost the models color.
 */

class BoostColor: public Effect {
public:
	BoostColor(GLfloat boost = 1.0f);
	virtual ~BoostColor() = default;
	void preDrawAction(core::Program* program);
	void postDrawAction(core::Program* program);
	void stopAction(core::Program* program);
	void startAction(core::Program* program);

private:
	GLfloat mBoost;
};

} /* effects*/
} /* fillwave */

#endif /* BOOSTCOLOR_H_ */
