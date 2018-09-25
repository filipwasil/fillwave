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

#include <flw/flc/rendering/Texture2DRenderableDynamic.h>

namespace flw {
namespace flc {

Texture2DRenderableDynamic::Texture2DRenderableDynamic(flc::TextureConfig* cfg, ParameterList& param, flc::Program* prog)
  : mTexture2DRenderable(GL_COLOR_ATTACHMENT0, cfg, param)
  , mProgram(prog)
  , mTimePassed(0.0f) {
  initUniformsCache();
}

void Texture2DRenderableDynamic::addTimeStep(GLfloat timePassed) {
  mTimePassed += timePassed;
}

void Texture2DRenderableDynamic::draw() {
  mProgram->use();
  mTexture2DRenderable.mTexture2D.bind(FILLWAVE_DIFFUSE_UNIT);
  flc::Uniform::push(mUniformLocationCacheTime, mTimePassed);
  mTexture2DRenderable.mTexture2D.unbind();
  flc::Program::disusePrograms();
}

void Texture2DRenderableDynamic::initUniformsCache() {
  mUniformLocationCacheTime = mProgram->getUniformLocation("uTime");
  mUniformLocationCachePostprocessingSampler = mProgram->getUniformLocation("uPostProcessingSampler");
}

void Texture2DRenderableDynamic::reload() {
  mTexture2DRenderable.reload();
  initUniformsCache();
}

} /* flc */
} /* flw */
