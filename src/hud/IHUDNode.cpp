/*
 * ProgressBar.cpp
 *
 *  Created on: Jan 11, 2016
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

#include <fillwave/hud/base/IHUDNode.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

/*! \class IHUDNode
 * \brief HUD base element.
 */

IHUDNode::IHUDNode(flc::Texture2D *texture, flc::Program *program, glm::vec2 position, glm::vec2 scale)
    : mTexture(texture)
    , mProgram(program)
    , mPosition(position)
    , mScale(scale) {
  mBlending = {
      GL_SRC_ALPHA,
      GL_ONE_MINUS_SRC_ALPHA
  };
}

IHUDNode::~IHUDNode() = default;

void IHUDNode::onAttached(ITreeNode* /*node*/) {
  // nothing
}

void IHUDNode::onDetached() {
  // nothing
}

void IHUDNode::draw() {
  if (nullptr == mTexture || NULL == mProgram) {
    fLogF("tried to draw a non drawable");
  }
  mProgram->use();
  mProgram->uniformPush("uPosition", mPosition);
  mProgram->uniformPush("uScale", mScale);
  coreDraw();
}

void IHUDNode::coreDraw() {
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(mBlending.mSrc, mBlending.mSrc);
  mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  mTexture->unbind();
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
}

} /* namespace flf */
} /* namespace flw */
