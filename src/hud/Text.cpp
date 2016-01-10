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
		pTexture2D texture,
		GLfloat startingPositionX,
		GLfloat startingPositionY,
		Engine* engine,
		GLfloat scale,
		Font* font,
		glm::vec4 color,
		eTextEffect effect)
		:
				Reloadable(engine),
				IHUD(std::make_shared<core::TextureRegion>(texture)),
				mEngine(engine),
				mText(text),
				mTexture(texture),
				mViewportWidth(engine->getScreenSize()[0]),
				mViewportHeight(engine->getScreenSize()[1]),
				mStartingX(startingPositionX),
				mStartingY(startingPositionY),
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

	mStartingX = tmpStartingX;

	mVBO = pVertexBufferText(
			new core::VertexBufferText(points_tmp, texcoords_tmp)); //xxx todo needs to be stored in kernel
	initVBO();
	initVAO();
}

inline void Text::createProgram() {
	ProgramLoader loader(mEngine);

	switch (mEffect) {
		case eTextEffect::eNone:
			mProgram = loader.getText();
			return;
		case eTextEffect::eBold:
			mProgram = loader.getTextBold();
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

} /* framework */
} /* fillwave */
