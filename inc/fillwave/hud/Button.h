/*
 * Button.h
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

#ifndef INC_FILLWAVE_HUD_BUTTON_H_
#define INC_FILLWAVE_HUD_BUTTON_H_

#include <fillwave/hud/base/IHUDNode.h>
#include <fillwave/common/IPickable.h>

namespace flw {
class Engine;
namespace flf {

/*! \class Button
 * \brief Pickable hud node.
 */

class Button : public IHUDNode, public IPickable {
public:
  Button(Engine *engine, flc::Texture2D *texture, glm::vec2 position, glm::vec2 scale);

  virtual ~Button() = default;

  /* IPickable */
  virtual void pick(glm::vec3 color) override;

  virtual void unpick() override;

  virtual void onPicked() override;

  virtual void onUnpicked() override;
};

} /* namespace flf */
typedef std::shared_ptr<flf::Button> pButton;
} /* namespace flw */

#endif /* INC_FILLWAVE_HUD_BUTTON_H_ */
