/*
 * RendererFR.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
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


#include <fillwave/renderers/RendererFR.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/Skybox.h>

namespace flw {
namespace flf {

void RendererFR::update(IRenderable *renderable) {
  mRenderPasses.push_back(renderable);
}

void RendererFR::draw(ICamera &camera) {
  if (mSkybox) {
    mSkybox->draw(camera);
  }
  glClear(GL_DEPTH_BUFFER_BIT);
  for (auto &node : mRenderPasses) {
    node->draw(camera);
  }
}

void RendererFR::reset(GLuint /*width*/, GLuint /*height*/) {
  mFlagReload = true;
}

void RendererFR::clear() {
  mFlagReload = true;

  size_t predictedSize = mRenderPasses.size() + 1;
  mRenderPasses.clear();
  mRenderPasses.reserve(predictedSize);
}

} /* namespace flf */
} /* namespace flw */
