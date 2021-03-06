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

#include <flw/flc/renderers/mRendererPBRP.h>
#include <flw/flc/pipeline/Program.h>
#include <flw/flf/models/Entity.h>
#include <flw/flf/models/Skybox.h>

namespace flw {
namespace flc {

void RendererPBRP::update(IRenderable *renderable) {
  RenderItem item;
  renderable->getRenderItem(item);
  GLuint programId = item.mHandles[RenderItem::eRenderHandleProgram];
  if (mRenderPasses.find(programId) != mRenderPasses.end()) {
    mRenderPasses[programId].push_back(renderable);
  } else {
    std::vector<IRenderable *> vector;
    vector.push_back(renderable);
    mRenderPasses[programId] = vector;
  }
}

void RendererPBRP::draw(ICamera &camera) {
  if (mSkybox) {
    mSkybox->draw(camera);
  }
  glClear(GL_DEPTH_BUFFER_BIT);
  for (auto &program : mRenderPasses) {
    Program::useProgram(program.first);
    for (auto &node : program.second) {
      node->drawPBRP(camera);
    }
  }
}

void RendererPBRP::reset(GLuint /*width*/, GLuint /*height*/) {
  mFlagReload = true;
}

void RendererPBRP::clear() {
  mFlagReload = true;

  size_t predictedSize = mRenderPasses.size() + 1;
  mRenderPasses.clear();
  mRenderPasses.reserve(predictedSize);
}

} /* flc */
} /* flw */
