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

#include <fillwave/models/effects/Fog.h>


namespace flw {
namespace flf {

Fog::Fog(glm::vec3 colour, GLfloat near, GLfloat far)
    : mColour(colour), mNearDistance(near), mFarDistance(far) {
}

void Fog::preDrawAction(flc::Program *program) {
  program->uniformPush("uFogEffect", true);
}

void Fog::postDrawAction(flc::Program *program) {
  program->uniformPush("uFogEffect", false);
}

void Fog::stopAction(flc::Program *program) {
  program->uniformPush("uFogEffect", false);
}

void Fog::startAction(flc::Program *program) {
  program->uniformPush("uFogEffect", true);
  program->uniformPush("uFogColor", mColour);
  program->uniformPush("uFogNearDistance", mNearDistance);
  program->uniformPush("uFogFarDistance", mFarDistance);
}

} /* flf */
} /* flw */
