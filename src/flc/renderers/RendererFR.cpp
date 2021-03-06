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

#include <flw/flc/renderers/mRendererFR.h>
#include <flw/flf/models/Entity.h>
#include <flw/flf/models/Skybox.h>

namespace flw {
namespace flc {

void RendererFR::update(IRenderable* renderable) {
  mRenderPasses.push_back(renderable);
}

void RendererFR::draw(ICamera& camera) {
  if (mSkybox) {
    mSkybox->draw(camera);
  }
  glClear(GL_DEPTH_BUFFER_BIT);
  for (auto &node : mRenderPasses) {
    node->drawFR(camera);
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

} /* flc */
} /* flw */
