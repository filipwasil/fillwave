/*
 * Programmable.cpp
 *
 *  Created on: May 15, 2015
 *      Author: filip
 */

#include <fillwave/models/base/Programmable.h>
#include <algorithm>

FLOGINIT("Programmable", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Programmable::Programmable(pProgram program) :
		mProgram(program) {

}

void Programmable::drawWithEffects(ICamera& camera) {

	core::Program* p = mProgram.get();

	/* Effects execution */
	p->use();
	std::for_each(mEffects.begin(), mEffects.end(),
		[p](pIEffect e) {e->preDrawAction(p);});
	core::Program::disusePrograms();

	/* Draw */
	for (auto& it : mChildren) {
		it->draw(camera);
	}

	/* Effects pre draw action */
	p->use();
	std::for_each(mEffects.begin(), mEffects.end(),
		[p](pIEffect e) {e->postDrawAction(p);});
	core::Program::disusePrograms();
}

void Programmable::drawWithEffectsDR(ICamera& camera) {

	core::Program* p = mProgram.get();

	/* Effects execution */
	std::for_each(mEffects.begin(), mEffects.end(),
		[p](pIEffect e) {e->preDrawAction(p);});

	/* Draw */
	for (auto& it : mChildren) {
		it->drawDR(camera);
	}

	/* Effects pre draw action */
	std::for_each(mEffects.begin(), mEffects.end(),
		[p](pIEffect e) {e->postDrawAction(p);});
}

void Programmable::drawWithEffectsPBRP(ICamera& camera) {

	core::Program* p = mProgram.get();

	/* Effects execution */
	std::for_each(mEffects.begin(), mEffects.end(),
		[p](pIEffect e) {e->preDrawAction(p);});

	/* Draw */
	for (auto& it : mChildren) {
		it->drawPBRP(camera);
	}

	/* Effects pre draw action */
	std::for_each(mEffects.begin(), mEffects.end(),
		[p](pIEffect e) {e->postDrawAction(p);});
}

void Programmable::addEffect(pIEffect effect) {
	auto _find_function = [effect](pIEffect& m) -> bool {return m == effect;};
	auto _begin = mEffects.begin();
	auto _end = mEffects.end();
	auto it = std::find_if(_begin, _end, _find_function);
	if (it != _end) {
		FLOG_DEBUG("Effect already added");
		return;
	}
	mEffects.push_back(effect);
	mProgram->use();
	effect->startAction(mProgram.get());
	core::Program::disusePrograms();
}

void Programmable::removeEffect(pIEffect effect) {
	auto _find_function = [effect](pIEffect& m) -> bool {return m == effect;};
	auto _begin = mEffects.begin();
	auto _end = mEffects.end();
	auto it = std::remove_if(_begin, _end, _find_function);
	mEffects.erase(it, _end);
	if (it != _end) {
		/* Start stop action */
		mProgram->use();
		effect->stopAction(mProgram.get());
		core::Program::disusePrograms();
	}
}

} /* framework */
} /* fillwave */
