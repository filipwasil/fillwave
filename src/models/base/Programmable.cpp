/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <fillwave/models/base/Programmable.h>

#include <fillwave/Log.h>

FLOGINIT("Programmable", FERROR | FFATAL)

namespace flw {
namespace flf {

Programmable::Programmable(flc::Program* program)
    : mProgram(program)
    , mEffects() {
  // nothing
}

Programmable::~Programmable() = default;

Programmable& Programmable::operator=(Programmable &&) = default;

Programmable::Programmable(Programmable&&) = default;

void Programmable::drawWithEffects(ICamera& camera) {

  flc::Program* p = mProgram;

  /* Effects execution */
  p->use();
  std::for_each(mEffects.begin(), mEffects.end(), [p](ps<IEffect>& e) {
    e->preDrawAction(p);
  });
  flc::Program::disusePrograms();

  /* Draw */
  for (auto &it : mChildren) {
    it->draw(camera);
  }

  /* Effects pre draw action */
  p->use();
  std::for_each(mEffects.begin(), mEffects.end(), [p](ps<IEffect>& e) {
    e->postDrawAction(p);
  });
  flc::Program::disusePrograms();
}

void Programmable::drawWithEffectsDR(ICamera &camera) {

  flc::Program *p = mProgram;

  /* Effects execution */
  std::for_each(mEffects.begin(), mEffects.end(), [p](ps<IEffect>& e) {
    e->preDrawAction(p);
  });

  /* Draw */
  for (auto &it : mChildren) {
    it->drawDR(camera);
  }

  /* Effects pre draw action */
  std::for_each(mEffects.begin(), mEffects.end(), [p](ps<IEffect>& e) {
    e->postDrawAction(p);
  });
}

void Programmable::drawWithEffectsPBRP(ICamera &camera) {

  flc::Program *p = mProgram;

  /* Effects execution */
  std::for_each(mEffects.begin(), mEffects.end(), [p](ps<IEffect>& e) {
    e->preDrawAction(p);
  });

  /* Draw */
  for (auto &it : mChildren) {
    it->drawPBRP(camera);
  }

  /* Effects pre draw action */
  std::for_each(mEffects.begin(), mEffects.end(), [p](ps<IEffect>& e) {
    e->postDrawAction(p);
  });
}

void Programmable::addEffect(ps<IEffect> effect) {
  auto _find_function = [effect](ps<IEffect>& m) -> bool {
    return m == effect;
  };
  auto it = std::remove_if(mEffects.begin(), mEffects.end(), _find_function);
  if (it != mEffects.end()) {
    fLogD("Effect already added");
    return;
  }
  mEffects.push_back(effect);
  mProgram->use();
  effect->startAction(mProgram);
  flc::Program::disusePrograms();
}

void Programmable::removeEffect(ps<IEffect> effect) {
  auto _find_function = [effect](ps<IEffect>& m) -> bool {
    return m == effect;
  };
  auto it = std::remove_if(mEffects.begin(), mEffects.end(), _find_function);
  if (it != mEffects.end()) {
    /* Start stop action */
    mProgram->use();
    effect->stopAction(mProgram);
    flc::Program::disusePrograms();
  }
  mEffects.erase(it, mEffects.end());
}

} /* flf */
} /* flw */
