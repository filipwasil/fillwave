/*
 * Programmable.cpp
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


#include <fillwave/models/base/Programmable.h>
#include <fillwave/Log.h>
#include <algorithm>

FLOGINIT("Programmable", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Programmable::Programmable(core::Program* program) :
	mProgram(program) {

}

void Programmable::drawWithEffects(ICamera& camera) {

	core::Program* p = mProgram;

	/* Effects execution */
	p->use();
	std::for_each(mEffects.begin(), mEffects.end(),
	[p](pIEffect & e) {
		e->preDrawAction(p);
	});
	core::Program::disusePrograms();

	/* Draw */
	for (auto& it : mChildren) {
		it->draw(camera);
	}

	/* Effects pre draw action */
	p->use();
	std::for_each(mEffects.begin(), mEffects.end(),
	[p](pIEffect & e) {
		e->postDrawAction(p);
	});
	core::Program::disusePrograms();
}

void Programmable::drawWithEffectsDR(ICamera& camera) {

	core::Program* p = mProgram;

	/* Effects execution */
	std::for_each(mEffects.begin(), mEffects.end(),
	[p](pIEffect & e) {
		e->preDrawAction(p);
	});

	/* Draw */
	for (auto& it : mChildren) {
		it->drawDR(camera);
	}

	/* Effects pre draw action */
	std::for_each(mEffects.begin(), mEffects.end(),
	[p](pIEffect & e) {
		e->postDrawAction(p);
	});
}

void Programmable::drawWithEffectsPBRP(ICamera& camera) {

	core::Program* p = mProgram;

	/* Effects execution */
	std::for_each(mEffects.begin(), mEffects.end(),
	[p](pIEffect & e) {
		e->preDrawAction(p);
	});

	/* Draw */
	for (auto& it : mChildren) {
		it->drawPBRP(camera);
	}

	/* Effects pre draw action */
	std::for_each(mEffects.begin(), mEffects.end(),
	[p](pIEffect & e) {
		e->postDrawAction(p);
	});
}

void Programmable::addEffect(pIEffect effect) {
	auto _find_function = [effect](pIEffect & m) -> bool {return m == effect;};
	auto it = std::remove_if(mEffects.begin(), mEffects.end(), _find_function);
	if (it != mEffects.end()) {
		fLogD("Effect already added");
		return;
	}
	mEffects.push_back(effect);
	mProgram->use();
	effect->startAction(mProgram);
	core::Program::disusePrograms();
}

void Programmable::removeEffect(pIEffect effect) {
	auto _find_function = [effect](pIEffect & m) -> bool {return m == effect;};
	auto it = std::remove_if(mEffects.begin(), mEffects.end(), _find_function);
	if (it != mEffects.end()) {
		/* Start stop action */
		mProgram->use();
		effect->stopAction(mProgram);
		core::Program::disusePrograms();
	}
	mEffects.erase(it, mEffects.end());
}

} /* framework */
} /* fillwave */
