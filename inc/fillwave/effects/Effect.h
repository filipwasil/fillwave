/*
 * Effect.h
 *
 *  Created on: Jul 19, 2014
 *      Author: Filip Wasil
 */

#ifndef EFFECT_H_
#define EFFECT_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace effects {

/*! \class Effect
 * \brief Base for effects.
 */

class Effect {
public:
	Effect();
	virtual ~Effect();

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

} /* effects */
typedef std::shared_ptr<effects::Effect> pEffect;
typedef std::unique_ptr<effects::Effect> puEffect;
} /* fillwave */

#endif /* EFFECT_H_ */
