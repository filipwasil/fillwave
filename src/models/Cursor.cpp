/*
 * Cursor.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
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


#include <fillwave/models/Cursor.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>

namespace flw {
namespace flf {

Cursor::Cursor(Engine *engine, flc::Texture *texture)
    : Impostor(engine, FILLWAVE_ENDLESS, 0.06f, texture)
    , mScreenFactor(static_cast<GLfloat>(engine->getScreenSize()[0]) / static_cast<GLfloat>(engine->getScreenSize()[1])) {

  mProgram = ProgramLoader(engine).getCursor();

  initUniformsCache();
}

void Cursor::move(glm::vec2 position) {
  mProgram->use();
  flc::Uniform::push(mULCPosition, position);
  flc::Program::disusePrograms();
}

void Cursor::draw() {
  mProgram->use();

  flc::Uniform::push(mULCScreenFactor, mScreenFactor);
  flc::Uniform::push(mULCSize, mSize);

  coreDraw();

  flc::Program::disusePrograms();
}

void Cursor::initUniformsCache() {
  mULCPosition = mProgram->getUniformLocation("uPosition");
  mULCScreenFactor = mProgram->getUniformLocation("uScreenFactor");
  mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
  mULCSize = mProgram->getUniformLocation("uSize");

  mProgram->use();
  flc::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);
  flc::Program::disusePrograms();
}

} /* flf */
} /* flw */
