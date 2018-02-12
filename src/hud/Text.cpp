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

#include <fillwave/hud/Text.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>

namespace flw {
namespace flf {

Text::Text(const std::string &text,
  flc::Texture2D *texture,
  glm::vec2 position,
  Engine *engine,
  GLfloat scale,
  Font *font,
  glm::vec4 color,
  ETextEffect effect)
  : IReloadable(engine)
  , Sprite(texture, createProgram(engine, effect), position, glm::vec2(scale, scale))
  , mText(text)
  , mColor(color)
  , mFont(font)
  , mEngine(engine)
  , mViewportWidth(engine->getScreenSize()[0])
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
    const int ascii_code = mText[i];

    const int atlas_col = (ascii_code - ' ') % mFont->mAtlasColumns;
    const int atlas_row = (ascii_code - ' ') / mFont->mAtlasColumns;

    const GLfloat s = atlas_col * (1.0f / mFont->mAtlasColumns);
    const GLfloat t = (atlas_row + 1) * (1.0f / mFont->mAtlasRows);

    const GLfloat x_pos = mPosition.x;
    const GLfloat y_pos = mPosition.y - mScale.x / mViewportHeight * mFont->mOffsets[ascii_code];

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

inline flc::Program* Text::createProgram(Engine *engine, ETextEffect effect) {
  switch (effect) {
    case ETextEffect::eBold:
      return ProgramLoader(engine).getProgram(EProgram::textBold);
    case ETextEffect::eNone:
      return ProgramLoader(engine).getProgram(EProgram::text);
  }
  return nullptr;
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
