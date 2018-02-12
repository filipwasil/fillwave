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

#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>

#include <fillwave/Log.h>

FLOGINIT("Texture2DRenderableDynamic", FERROR | FFATAL | FDEBUG)

namespace flw {
namespace flc {

Texture2DRenderableDynamic::Texture2DRenderableDynamic(flc::TextureConfig* cfg, ParameterList& param, flc::Program* prog)
    : Texture2DRenderable(GL_COLOR_ATTACHMENT0, cfg, param)
    , mProgram(prog)
    , mTimePassed(0.0f) {
  initUniformsCache();
}

void Texture2DRenderableDynamic::draw(GLfloat timePassed) {
  mTimePassed += timePassed;
  mProgram->use();
  bind(FILLWAVE_DIFFUSE_UNIT);
  flc::Uniform::push(mUniformLocationCacheTime, mTimePassed);
  glEnable(GL_BLEND);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisable(GL_BLEND);
  unbind();
  flc::Program::disusePrograms();
}

void Texture2DRenderableDynamic::initUniformsCache() {
  mUniformLocationCacheTime = mProgram->getUniformLocation("uTime");
  mUniformLocationCachePostprocessingSampler = mProgram->getUniformLocation("uPostProcessingSampler");
}

void Texture2DRenderableDynamic::reload() {
  fLogD("Reload");
  Texture2DRenderable::reload();
  initUniformsCache();
}

} /* flc */
} /* flw */
