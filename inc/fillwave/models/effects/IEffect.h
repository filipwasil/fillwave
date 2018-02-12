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

#include <fillwave/core/pipeline/Program.h>

namespace flw {
namespace flf {

/*! \class IEffect
 * \brief Base for effects.
 */

class IEffect {
public:
  IEffect();

  virtual ~IEffect();

  /*!
   * preDrawAction
   * \brief virtual: defines action to be done just before the draw.
   */

  virtual void preDrawAction(flc::Program* program) = 0;

  /*!
   * postDrawAction
   * \brief virtual: defines action to be done just after the draw.
   */

  virtual void postDrawAction(flc::Program* program) = 0;

  /*!
   * stopAction
   * \brief virtual: defines action to be done when the effect is stopped.
   */

  virtual void stopAction(flc::Program* program) = 0;

  /*!
   * startAction
   * \brief virtual: defines action to be done when the effect is started.
   */

  virtual void startAction(flc::Program* program) = 0;
};

} /* flf */
} /* flw */
