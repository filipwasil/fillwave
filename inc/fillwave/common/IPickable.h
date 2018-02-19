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

#include <fillwave/Math.h>

namespace flw {
namespace flf {

/*! \class IPickable
 * \brief Pickable Interface.
 */

class IPickable {
public:
  IPickable();

  virtual ~IPickable();

  IPickable& operator=(const IPickable&);

  IPickable(const IPickable&);

  bool isPickable();

  glm::vec3 getPickableColor();

  virtual void assignColor(const glm::vec3& color) = 0;

  virtual void unpick() = 0;

  virtual void onPicked() = 0;

  virtual void onUnpicked() = 0;

protected:
  bool mFlagPickable;
  glm::vec3 mPickColor;
};

} /* namespace flf */
} /* namespace flw */
