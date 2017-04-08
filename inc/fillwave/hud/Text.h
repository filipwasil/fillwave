/*
 * Text.h
 *
 *  Created on: Jul 26, 2014
 *      Author: Filip Wasil
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

#ifndef TEXT_H_
#define TEXT_H_

#include <fillwave/core/buffers/VertexBufferText.h>
#include <fillwave/core/pipeline/Program.h>

#include <fillwave/hud/base/IHUDNode.h>
#include <fillwave/loaders/FontLoader.h>
#include <fillwave/models/base/IReloadable.h>
#include <map>

namespace flw {
class Engine;

enum class eTextEffect {
  eNone
  , eBold
};

namespace flf {

/*! \class Text
 * \brief 2D Text on the screen.
 */

class Text : public IReloadable, public IHUDNode {
public:
  Text(const std::string &text,
      flc::Texture2D *texture,
      glm::vec2 position,
      Engine *engine,
      GLfloat scale,
      Font *font,
      glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0),
      eTextEffect effect = eTextEffect::eNone);

  virtual ~Text() = default;

  void draw() override;

  void editAspectRatio(Engine *engine);

  void editString(std::string text);

  void editColor(glm::vec4 color);

  void editSize(GLfloat size);

  void editPosition(glm::vec2 position);

private:
  /* Text */
  std::string mText;
  glm::vec4 mColor;
  eTextEffect mEffect;
  Font *mFont;
  flc::VertexBufferText *mVBO;

  /* IHUD */
  Engine *mEngine;
  GLint mUniformLocationCacheColor, mUniformLocationCacheTextureUnit;
  GLint mViewportWidth, mViewportHeight;

  flc::Program *createProgram(Engine *engine, eTextEffect effect);

  void createVBO();

  void clearVBO();

  void initVBO();

  void initVAO();

  void initBuffers();

  void initPipeline();

  void initUniformsCache();
};

} /* flf */
typedef std::shared_ptr<flf::Text> pText;
typedef std::unique_ptr<flf::Text> puText;
} /* flw */

#endif /* TEXT_H_ */
