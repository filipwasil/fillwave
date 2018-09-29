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

#include <flw/flf/models/EmiterPointStep.h>

#include <flw/Fillwave.h>

namespace flw {
namespace flf {

EmiterPointStep::EmiterPointStep(
  Engine *engine
  , GLint howMany
  , GLenum blendingSource
  , GLenum blendingDestination
  , flc::Texture2D* texture)
  : IReloadable(engine)
  , Entity()
  , IEmiterPoint(
  howMany
  , 100
  , 1
  , texture
  , glm::vec4(1.0, 1.0, 1.0, 0.0)
  , blendingSource
  , blendingDestination
  , GL_FALSE
  , 1.0) {
  // nothing
}

EmiterPointStep::~EmiterPointStep() = default;

} /* flf */
} /* flw */
