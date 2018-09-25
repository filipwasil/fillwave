#pragma once

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

#include <flw/flc/texturing/Texture2D.h>
#include <flw/flc/pipeline/Program.h>
#include <flw/flc/pipeline/Blending.h>

#include <flw/flf/models/base/ITreeNode.h>

namespace flw {
namespace flf {

/*! \class Sprite
 * \brief HUD base element.
 */

class Sprite : public ITreeNode {
public:
  Sprite(flc::Texture2D* texture = nullptr,
      flc::Program* program = nullptr,
      glm::vec2 position = glm::vec2(0.0f, 0.0f),
      glm::vec2 scale = glm::vec2(1.0f, 1.0f));

  virtual ~Sprite();

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

} /* flf */
} /* flw */
