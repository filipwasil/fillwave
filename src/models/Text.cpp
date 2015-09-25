/*
 * Text.cpp
 *
 *  Created on: Jul 26, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/models/Text.h>

#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/Fillwave.h>

#include <fillwave/extras/Log.h>

FLOGINIT("Text", FERROR | FFATAL)

namespace fillwave {
namespace models {

Text::Text(
		std::string& text,
		pTexture texture,
		GLfloat startingPositionX,
		GLfloat startingPositionY,
		Engine* engine,
		GLfloat scale,
		Font* font,
		glm::vec4 color,
		eTextEffect effect)
		:
				Reloadable(engine),
				mEngine(engine),
				mText(text),
				mTexture(texture),
				mViewportWidth(engine->getScreenSize()[0]),
				mViewportHeight(engine->getScreenSize()[1]),
				mStartingX(startingPositionX),
				mStartingY(startingPositionY),
				mVBO(pVertexBufferText()),
				mScale(scale),
				mFont(font),
				mColor(color),
				mEffect(effect) {

	mBlending.mSource = GL_SRC_ALPHA;
	mBlending.mDestination = GL_ONE_MINUS_SRC_ALPHA;

	createProgram();
	initPipeline();
	createVBO();
	initUniformsCache();
}

Text::~Text() {

}

void Text::draw() {
	mVAO->bind();
	mProgram->use();
	mVBO->send();
	mTexture->bind(FILLWAVE_DIFFUSE_UNIT);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(mBlending.mSource, mBlending.mDestination);

	core::Uniform::push(mUniformLocationCacheTextureUnit, FILLWAVE_DIFFUSE_UNIT);

	glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	mTexture->unbind();
	mVAO->unbind();
	core::Program::disusePrograms();
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
	mScale = size;
	clearVBO();
	createVBO();
}

void Text::editPosition(GLfloat startingX, GLfloat startingY) { //xxx optimize
	mStartingX = startingX;
	mStartingY = startingY;
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

	GLfloat tmpStartingX = mStartingX;

	for (int i = 0; i < lenght; i++) {
		int ascii_code = mText[i];

		int atlas_col = (ascii_code - ' ') % mFont->mAtlasColumns;
		int atlas_row = (ascii_code - ' ') / mFont->mAtlasColumns;

		GLfloat s = atlas_col * (1.0 / mFont->mAtlasColumns);
		GLfloat t = (atlas_row + 1) * (1.0 / mFont->mAtlasRows);

		GLfloat x_pos = mStartingX;
		GLfloat y_pos = mStartingY
				- mScale / mViewportHeight * mFont->mOffsets[ascii_code];

		if (i + 1 < lenght) {
			mStartingX += mFont->mWidths[ascii_code] * mScale / mViewportWidth;
		}

		points_tmp.push_back(x_pos);
		points_tmp.push_back(y_pos);
		points_tmp.push_back(x_pos);
		points_tmp.push_back(y_pos - mScale / mViewportHeight);
		points_tmp.push_back(x_pos + mScale / mViewportWidth);
		points_tmp.push_back(y_pos - mScale / mViewportHeight);

		points_tmp.push_back(x_pos + mScale / mViewportWidth);
		points_tmp.push_back(y_pos - mScale / mViewportHeight);
		points_tmp.push_back(x_pos + mScale / mViewportWidth);
		points_tmp.push_back(y_pos);
		points_tmp.push_back(x_pos);
		points_tmp.push_back(y_pos);

		texcoords_tmp.push_back(s);
		texcoords_tmp.push_back(1.0 - t + 1.0 / mFont->mAtlasRows);
		texcoords_tmp.push_back(s);
		texcoords_tmp.push_back(1.0 - t);
		texcoords_tmp.push_back(s + 1.0 / mFont->mAtlasColumns);
		texcoords_tmp.push_back(1.0 - t);

		texcoords_tmp.push_back(s + 1.0 / mFont->mAtlasColumns);
		texcoords_tmp.push_back(1.0 - t);
		texcoords_tmp.push_back(s + 1.0 / mFont->mAtlasColumns);
		texcoords_tmp.push_back(1.0 - t + 1.0 / mFont->mAtlasRows);
		texcoords_tmp.push_back(s);
		texcoords_tmp.push_back(1.0 - t + 1.0 / mFont->mAtlasRows);
	}

	mStartingX = tmpStartingX;

	mVBO = pVertexBufferText(
			new core::VertexBufferText(points_tmp, texcoords_tmp)); //xxx todo needs to be stored in kernel
	initVBO();
	initVAO();
}

inline void Text::createProgram() {
	loader::ProgramLoader loader;

	switch (mEffect) {
		case eTextEffect::none:
			mProgram = loader.getText(mEngine);
			return;
		case eTextEffect::bold:
			mProgram = loader.getTextBold(mEngine);
			return;
	}
}

inline void Text::initBuffers() {
	mVBO->reload();
}

inline void Text::initPipeline() {
	mProgram->use();
	mProgram->uniformPush("uColour", mColor);
	core::Program::disusePrograms();
}

inline void Text::initUniformsCache() {
	mUniformLocationCacheColor = mProgram->getUniformLocation("uColour");
	mUniformLocationCacheTextureUnit = mProgram->getUniformLocation(
			"uTextureUnit");
}

inline void Text::initVAO() {
	mSampler->bind();
	mVAO->bind();
	mVBO->bind();
	mVBO->setReady();
	mVBO->send();
	mVBO->attributesSetForVAO();
	mVAO->unbind();
}

inline void Text::initVBO() {
	mVBO->getAttributes(mProgram->getHandle());
	mVBO->attributesBind(mProgram);
}

} /* models */
} /* fillwave */
