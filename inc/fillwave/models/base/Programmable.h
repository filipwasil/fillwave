/*
 * Programmable.h
 *
 *  Created on: May 15, 2015
 *      Author: filip
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

#ifndef SRC_MODELS_PROGRAMMABLE_H_
#define SRC_MODELS_PROGRAMMABLE_H_

#include <fillwave/models/Entity.h>
#include <fillwave/models/effects/Effect.h>

namespace fillwave {
namespace framework {

/*! \class Programmable
 * \brief Entity for which is it possible to add/remove Effect objects.
 */

class Programmable: public Entity {
 public:
	Programmable(core::Program* program);

	virtual ~Programmable() = default;

	void addEffect(pIEffect effect);
	void removeEffect(pIEffect effect);
	void drawWithEffects(ICamera& camera);
	void drawWithEffectsDR(ICamera& camera);
	void drawWithEffectsPBRP(ICamera& camera);

 protected:
	core::Program* mProgram;

	std::vector<pIEffect> mEffects;
};

} /* framework */
} /* fillwave */

#endif /* SRC_MODELS_PROGRAMMABLE_H_ */
