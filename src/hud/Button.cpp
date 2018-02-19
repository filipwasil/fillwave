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

#include <fillwave/hud/Button.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>

namespace flw {
namespace flf {

Button::Button(Engine *engine, flc::Texture2D *texture, glm::vec2 position, glm::vec2 scale)
    : Sprite(texture
    , ProgramLoader(engine).getProgram(EProgram::hud)
    , position
    , glm::vec2(scale.x, scale.y * engine->getScreenAspectRatio())) {
  // nothing
}

void Button::assignColor(const glm::vec3& color) {
  mFlagPickable = true;
  mPickColor = color;
}

void Button::unpick() {
  mFlagPickable = false;
}

void Button::onPicked() {
  // nothing
}

void Button::onUnpicked() {
  // nothing
}

} /* flf */
} /* flw */
