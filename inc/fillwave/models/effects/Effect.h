/*
 * Effect.h
 *
 *  Created on: Jul 19, 2014
 *      Author: Filip Wasil
 */

#ifndef EFFECT_H_
#define EFFECT_H_

#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace framework {

/*! \class IEffect
 * \brief Base for effects.
 */

class IEffect {
 public:
	IEffect() = default;
	virtual ~IEffect() = default;

	/*!
	 * preDrawAction
	 * \brief virtual: defines action to be done just before the draw.
	 */

	virtual void preDrawAction(core::Program* program) = 0;

	/*!
	 * postDrawAction
	 * \brief virtual: defines action to be done just after the draw.
	 */

	virtual void postDrawAction(core::Program* program) = 0;

	/*!
	 * stopAction
	 * \brief virtual: defines action to be done when the effect is stopped.
	 */

	virtual void stopAction(core::Program* program) = 0;

	/*!
	 * startAction
	 * \brief virtual: defines action to be done when the effect is started.
	 */

	virtual void startAction(core::Program* program) = 0;
};

} /* framework */
typedef std::shared_ptr<framework::IEffect> pIEffect;
typedef std::unique_ptr<framework::IEffect> puIEffect;
} /* fillwave */

#endif /* EFFECT_H_ */
