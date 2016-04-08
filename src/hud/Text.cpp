/*
 * Text.cpp
 *
 *  Created on: Jul 26, 2014
 *      Author: filip
 */

#include <fillwave/hud/Text.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>

FLOGINIT("Text", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Text::Text(
    std::string& text,
    core::Texture2D* texture,
    glm::vec2 position,
    Engine* engine,
    GLfloat scale,
    Font* font,
    glm::vec4 color,
    eTextEffect effect) :
	IReloadable(engine),
	IHUDNode(texture, createProgram(engine, effect), position,
	         glm::vec2(scale, scale)),
	mText(text),
	mColor(color),
	mEffect(effect),
	mFont(font),
	mEngine(engine),
	mViewportWidth(engine->getScreenSize()[0]),
	mViewportHeight(engine->getScreenSize()[1]) {

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
	core::VertexArray::unbindVAO();
}

inline void Text::clearVBO() {
	mVBO.reset();
}

void Text::editString(std::string text) {
	mText = text;
	clearVBO();
	createVBO();
}

void Text::editColor(glm::vec4 color) {
	mColor = color;
	mProgram->use();
	core::Uniform::push(mUniformLocationCacheColor, mColor);
	core::Program::disusePrograms();
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

void Text::editAspectRatio(Engine* engine) {
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

		GLfloat s = atlas_col * (1.0 / mFont->mAtlasColumns);
		GLfloat t = (atlas_row + 1) * (1.0 / mFont->mAtlasRows);

		GLfloat x_pos = mPosition.x;
		GLfloat y_pos = mPosition.y
		                - mScale.x / mViewportHeight * mFont->mOffsets[ascii_code];

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

	mVBO = std::make_shared < core::VertexBufferText
	       > (points_tmp, texcoords_tmp); //xxx todo needs to be stored in kernel
	initVBO();
	initVAO();
}

inline pProgram Text::createProgram(Engine* engine, eTextEffect effect) {
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
	core::Program::disusePrograms();
}

inline void Text::initUniformsCache() {
	mUniformLocationCacheColor = mProgram->getUniformLocation("uColour");
}

inline void Text::initVAO() {
	mSampler->bind();
	mVAO->bind();
	mVBO->bind();
	mVBO->setReady();
	mVBO->send();
	mVBO->attributesSetForVAO();
	core::VertexArray::unbindVAO();
}

inline void Text::initVBO() {
	mVBO->getAttributes(mProgram->getHandle());
	mVBO->attributesBind(mProgram);
}

} /* framework */
} /* fillwave */
