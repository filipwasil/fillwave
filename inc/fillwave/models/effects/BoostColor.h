/*
 * BoostColor.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Filip Wasil
 */

#ifndef BOOSTCOLOR_H_
#define BOOSTCOLOR_H_

#include <fillwave/models/effects/Effect.h>

namespace fillwave {
namespace framework {

/*! \class BoostColor
 * \brief Effect to boost the models color.
 */

class BoostColor: public IEffect {
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

} /* framework*/
} /* fillwave */

#endif /* BOOSTCOLOR_H_ */
