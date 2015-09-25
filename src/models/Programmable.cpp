/*
 * Programmable.cpp
 *
 *  Created on: May 15, 2015
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2012 - 2015 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/models/Programmable.h>
#include <algorithm>

FLOGINIT("Programmable", FERROR | FFATAL)

namespace fillwave {
namespace models {

Programmable::Programmable(pProgram program)
		: mProgram(program) {

}

Programmable::~Programmable() {

}

void Programmable::drawWithEffects(space::Camera& camera) {

	core::Program* p = mProgram.get();

	/* Effects execution */
	p->use();
	std::for_each(mEffects.begin(), mEffects.end(),
			[p](pEffect e) {e->preDrawAction(p);});
	core::Program::disusePrograms();

	/* Draw */
	for (auto& it : mChildren) {
		it->draw(camera);
	}

	/* Effects pre draw action */
	p->use();
	std::for_each(mEffects.begin(), mEffects.end(),
			[p](pEffect e) {e->postDrawAction(p);});
	core::Program::disusePrograms();
}

void Programmable::drawWithEffectsDR(space::Camera& camera) {

	core::Program* p = mProgram.get();

	/* Effects execution */
	p->use();
	std::for_each(mEffects.begin(), mEffects.end(),
			[p](pEffect e) {e->preDrawAction(p);});
	core::Program::disusePrograms();

	/* Draw */
	for (auto& it : mChildren) {
		it->drawDR(camera);
	}

	/* Effects pre draw action */
	p->use();
	std::for_each(mEffects.begin(), mEffects.end(),
			[p](pEffect e) {e->postDrawAction(p);});
	core::Program::disusePrograms();
}

void Programmable::addEffect(pEffect effect) {
	auto _find_function = [effect](pEffect m) -> bool {return m == effect;};
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

void Programmable::removeEffect(pEffect effect) {
	auto _find_function = [effect](pEffect m) -> bool {return m == effect;};
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

} /* models */
} /* fillwave */
