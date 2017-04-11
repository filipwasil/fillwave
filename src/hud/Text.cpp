/*
 * Text.cpp
 *
 *  Created on: Jul 26, 2014
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


#include <fillwave/hud/Text.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>


namespace flw {
namespace flf {

Text::Text(const std::string &text,
    flc::Texture2D *texture,
    glm::vec2 position,
    Engine *engine,
    GLfloat scale,
    Font *font,
    glm::vec4 color,
    eTextEffect effect)
    : IReloadable(engine), IHUDNode(texture, createProgram(engine, effect), position, glm::vec2(scale, scale)), mText(
    text), mColor(color), mEffect(effect), mFont(font), mEngine(engine), mViewportWidth(engine->getScreenSize()[0])
    , mViewportHeight(engine->getScreenSize()[1]) {

  initPipeline();
  createVBO();
  initUniformsCache();
}

void Text::draw() {
  mProgram->use();

  mVAO->bind();
  mVBO->send();
  mTexture->bind(FILLWAVE_DIFFUSE_UNIT);

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(mBlending.mSrc, mBlending.mDst);
  glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  mTexture->unbind();
  flc::VertexArray::unbindVAO();
}

inline void Text::clearVBO() {
  mEngine->removeBufferText(mVAO);
}

void Text::editString(std::string text) {
  mText = text;
  clearVBO();
  createVBO();
}

void Text::editColor(glm::vec4 color) {
  mColor = color;
  mProgram->use();
  flc::Uniform::push(mUniformLocationCacheColor, mColor);
  flc::Program::disusePrograms();
}

void Text::editSize(GLfloat size) { //xxx optimize
  mScale = glm::vec2(size, size);
  clearVBO();
  createVBO();
}

void Text::editPosition(glm::vec2 position) { //xxx optimize
  mPosition = position;
  clearVBO();
  createVBO();
}

void Text::editAspectRatio(Engine *engine) {
  mViewportWidth = engine->getScreenSize()[0];
  mViewportHeight = engine->getScreenSize()[1];
  clearVBO();
  createVBO();
}

void Text::createVBO() {
  int lenght = mText.length();

  std::vector<GLfloat> points_tmp;
  std::vector<GLfloat> texcoords_tmp;

  points_tmp.reserve(lenght * 12);
  texcoords_tmp.reserve(lenght * 12);

  GLfloat tmpStartingX = mPosition.x;

  for (int i = 0; i < lenght; i++) {
    int ascii_code = mText[i];

    int atlas_col = (ascii_code - ' ') % mFont->mAtlasColumns;
    int atlas_row = (ascii_code - ' ') / mFont->mAtlasColumns;

    GLfloat s = atlas_col * (1.0f / mFont->mAtlasColumns);
    GLfloat t = (atlas_row + 1) * (1.0f / mFont->mAtlasRows);

    GLfloat x_pos = mPosition.x;
    GLfloat y_pos = mPosition.y - mScale.x / mViewportHeight * mFont->mOffsets[ascii_code];

    if (i + 1 < lenght) {
      mPosition.x += mFont->mWidths[ascii_code] * mScale.x / mViewportWidth;
    }

    points_tmp.push_back(x_pos);
    points_tmp.push_back(y_pos);
    points_tmp.push_back(x_pos);
    points_tmp.push_back(y_pos - mScale.x / mViewportHeight);
    points_tmp.push_back(x_pos + mScale.x / mViewportWidth);
    points_tmp.push_back(y_pos - mScale.x / mViewportHeight);

    points_tmp.push_back(x_pos + mScale.x / mViewportWidth);
    points_tmp.push_back(y_pos - mScale.x / mViewportHeight);
    points_tmp.push_back(x_pos + mScale.x / mViewportWidth);
    points_tmp.push_back(y_pos);
    points_tmp.push_back(x_pos);
    points_tmp.push_back(y_pos);

    texcoords_tmp.push_back(s);
    texcoords_tmp.push_back(1.0f - t + 1.0f / mFont->mAtlasRows);
    texcoords_tmp.push_back(s);
    texcoords_tmp.push_back(1.0f - t);
    texcoords_tmp.push_back(s + 1.0f / mFont->mAtlasColumns);
    texcoords_tmp.push_back(1.0f - t);

    texcoords_tmp.push_back(s + 1.0f / mFont->mAtlasColumns);
    texcoords_tmp.push_back(1.0f - t);
    texcoords_tmp.push_back(s + 1.0f / mFont->mAtlasColumns);
    texcoords_tmp.push_back(1.0f - t + 1.0f / mFont->mAtlasRows);
    texcoords_tmp.push_back(s);
    texcoords_tmp.push_back(1.0f - t + 1.0f / mFont->mAtlasRows);
  }

  mPosition.x = tmpStartingX;


  mVBO = mEngine->storeBuffer<flc::VertexBufferText>(mVAO, points_tmp, texcoords_tmp);

  initVBO();
  initVAO();
}

inline flc::Program *Text::createProgram(Engine *engine, eTextEffect effect) {
  switch (effect) {
    case eTextEffect::eBold:
      return ProgramLoader(engine).getTextBold();
    case eTextEffect::eNone:
    default:
      return ProgramLoader(engine).getText();
  }
}

inline void Text::initBuffers() {
  mVBO->reload();
}

inline void Text::initPipeline() {
  mProgram->use();
  mProgram->uniformPush("uColour", mColor);
  mProgram->uniformPush("uTextureUnit", FILLWAVE_DIFFUSE_UNIT);
  flc::Program::disusePrograms();
}

inline void Text::initUniformsCache() {
  mUniformLocationCacheColor = mProgram->getUniformLocation("uColour");
}

inline void Text::initVAO() {
  mSampler->bind();
  mVAO->bind();
  mVBO->bind();
  mVBO->setLoaded(GL_FALSE);
  mVBO->send();
  mVBO->attributesSetForVAO();
  flc::VertexArray::unbindVAO();
}

inline void Text::initVBO() {
  mVBO->initAttributes(mProgram->getHandle());
}

} /* flf */
} /* flw */
