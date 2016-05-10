/*
 * Effect.h
 *
 *  Created on: Jul 19, 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
