#pragma once

/*
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

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/pipeline/Program.h>
#include <fillwave/core/pipeline/Blending.h>

#include <fillwave/models/base/ITreeNode.h>

namespace flw {
namespace flf {

/*! \class IHUDNode
 * \brief HUD base element.
 */

class IHUDNode : public ITreeNode {
public:
  IHUDNode(flc::Texture2D* texture = nullptr,
      flc::Program* program = nullptr,
      glm::vec2 position = glm::vec2(0.0f, 0.0f),
      glm::vec2 scale = glm::vec2(1.0f, 1.0f));

  virtual ~IHUDNode() override;

  virtual void draw();

  void onAttached(ITreeNode *node) override;

  void onDetached() override;

  void coreDraw();

protected:
  flc::Texture2D* mTexture;
  flc::Program* mProgram;
  glm::vec2 mPosition;
  glm::vec2 mScale;
  Blending mBlending;
};

} /* namespace flf */
typedef std::shared_ptr<flf::IHUDNode> pIHUDNode;
} /* namespace flw */
