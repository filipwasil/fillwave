#pragma once

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

#include <flw/flf/models/Entity.h>
#include <flw/flf/models/effects/IEffect.h>

namespace flw {
namespace flf {

/*! \class Programmable
 * \brief Entity for which is it possible to add/remove Effect objects.
 */

class Programmable : public Entity {
public:
  Programmable(flc::Program *program);

  ~Programmable() override;

  Programmable& operator=(const Programmable &) = delete;

  Programmable(const Programmable &) = delete;

  Programmable& operator=(Programmable &&);

  Programmable(Programmable&& obj);

  void addEffect(ps<IEffect> effect);

  void removeEffect(ps<IEffect> effect);

  void drawWithEffects(ICamera& camera);

  void drawWithEffectsDR(ICamera& camera);

  void drawWithEffectsPBRP(ICamera& camera);

protected:
  flc::Program* mProgram;
  std::vector<ps<IEffect>> mEffects;
};

} /* flf */
} /* flw */
