/*
 * ProgressBar.h
 *
 *  Created on: Jan 11, 2016
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

#ifndef INC_FILLWAVE_HUD_PROGRESSBAR_H_
#define INC_FILLWAVE_HUD_PROGRESSBAR_H_

#include <fillwave/hud/base/IHUDNode.h>
#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/core/pipeline/Program.h>

namespace flw {
class Engine;
namespace flf {

/*! \class ProgressBar
 * \brief HUD node to indicate progress.
 */

class ProgressBar : public IHUDNode {
public:
  ProgressBar(Engine *engine,
      flc::Texture2D *texture,
      const std::string &shaderPath,
      glm::vec2 position,
      glm::vec2 scale);

  virtual ~ProgressBar() = default;

  void setProgress(GLfloat progress);

  void draw() override;

private:
  GLfloat mProgress;
};

} /* namespace flf */
typedef std::shared_ptr<flf::ProgressBar> pProgressBar;
} /* namespace flw */

#endif /* INC_FILLWAVE_HUD_PROGRESSBAR_H_ */
