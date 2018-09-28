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

#include <flw/flf/models/MeshOcclusion.h>
#include <flw/flf/loaders/ProgramLoader.h>
#include <flw/flf/models/shapes/BoxOcclusion.h>
#include <flw/flf/space/Scene.h>
#include <flw/Fillwave.h>

namespace flw {
namespace flf {

MeshOcclusion::MeshOcclusion(Engine* engine)
  : IReloadable (engine, engine->storeVAO(this))
  , mEngine (engine)
  , mProgram (ProgramLoader(engine).getProgram(flf::EProgram::occlusionOptimizedQuery)) {
}

MeshOcclusion::~MeshOcclusion() {
  // nothing
}

void MeshOcclusion::initBuffers() {
  // nothing
}

void MeshOcclusion::initPipeline() {
 // nothing
}


void MeshOcclusion::initUniformsCache() {
 // nothing
}

void MeshOcclusion::initVAO() {
  mVAO->bind();
  mVBO->bind();
  mVBO->attributesSetForVAO();
  mVBO->send();
  flc::VertexArray::unbindVAO();
}

void MeshOcclusion::initVBO() {
  vec<flc::VertexPosition> vec = flf::BoxOcclusion().getVertices();
  mVBO = mEngine->storeBuffer<flc::VertexBufferPosition>(mVAO, vec);
  mVBO->initAttributes(mProgram->getHandle());
}

void MeshOcclusion::reload() {
  IReloadable::reload();
}

void MeshOcclusion::draw(Scene& scene) {
  glDisable(GL_CULL_FACE);
  glDepthMask(GL_FALSE);
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  scene.drawOcclusion();
  glEnable(GL_CULL_FACE);
  glDepthMask(GL_TRUE);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  flc::VertexArray::unbindVAO();
}

} /* flf */
} /* flw */
