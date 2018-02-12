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

#include <fillwave/Fillwave.h>

#include <fillwave/models/base/IReloadable.h>

namespace flw {
namespace flf {

IReloadable::IReloadable(Engine* engine, flc::VertexArray* vao)
    : mVAO(vao ? vao : engine->storeVAO(this))
    , mSampler(engine->storeSO(FILLWAVE_DIFFUSE_UNIT)) {
  mSampler->bind();
  mSampler->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  mSampler->setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  mSampler->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}

IReloadable::~IReloadable() = default;

void IReloadable::reload() {
  initBuffers();
  initPipeline();
  initVBO();
  initVAO();
  initUniformsCache();
}

} /* flf */
} /* flw */
